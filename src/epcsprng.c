#include "../include/epcsprng.h"
#include "../include/util.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include <string.h>
#include <sys/random.h>

#include <mbedtls/aes.h>

#ifndef MBEDTLS_CIPHER_MODE_CTR
#error "EPCSPRNG requires AES CTR to be available"
#endif

struct EPCSPRNG {
    union {
        uint8_t _8[16];
        uint32_t _32[4];
        uint64_t _64[2];
    } nonce;
    mbedtls_aes_context aes_ctx;
};

EPCSPRNG *epcsprng_new(uint8_t const *const key, size_t const keylen_octets) {
    switch (keylen_octets) {
    case 128 / 8: // intentional fallthrough
    case 192 / 8: // intentional fallthrough
    case 256 / 8: // intentional fallthrough
        break;
    default:
        return NULL;
    }
    EPCSPRNG *ctx = malloc(sizeof(EPCSPRNG));
    if (NULL != ctx) {
        mbedtls_aes_init(&ctx->aes_ctx);
        mbedtls_aes_setkey_enc(&ctx->aes_ctx, key,
                               (unsigned int)keylen_octets * 8);
        explicit_bzero(ctx->nonce._8, 16);
        const int return_value = getentropy(ctx->nonce._8, 16);
        if (return_value) {
            free(ctx);
            return NULL;
        }
    }
    return ctx;
}

EPCSPRNG *epcsprng_new_auto_key(void) {
    uint8_t key[16];
    const bool ok = !getentropy(key, 16);
    if (!ok) {
        return NULL;
    }
    return epcsprng_new(key, 16);
}

void epcsprng_destroy(EPCSPRNG *const rng) {
    if (NULL != rng) {
        mbedtls_aes_free(&rng->aes_ctx);
    }
    free(rng);
}

bool epcsprng_auto_rekey(EPCSPRNG *const rng) {
    uint8_t key[16];
    const bool ok = !getentropy(key, 16);
    return ok && epcsprng_rekey(rng, key, 16);
}

bool epcsprng_rekey(EPCSPRNG *const rng, uint8_t const *const key,
                    size_t const keylen_octets) {
    return !mbedtls_aes_setkey_enc(&rng->aes_ctx, key,
                                   (unsigned int)keylen_octets * 8);
}

static bool fill_blocks(uint8_t *const buffer, size_t const length_octets,
                        EPCSPRNG *rng) {
    // TODO alignof/alignas such that we can vectorize writes
    uint8_t block[16];
    explicit_bzero(block, 16);
    size_t nc_off = 0;
    const int res = mbedtls_aes_crypt_ctr(&rng->aes_ctx, length_octets, &nc_off,
                                          rng->nonce._8, block, buffer, buffer);
    explicit_bzero(block, 16);
    return 0 == res;
}

static bool fill_partial_block(uint8_t *const buffer, size_t const length_octets,
                               EPCSPRNG *rng) {
    // TODO alignof/alignas such that we can vectorize writes
    uint8_t block[16], temp[16];
    explicit_bzero(block, 16);
    explicit_bzero(temp, 16);
    size_t nc_off = 0;
    const int res = mbedtls_aes_crypt_ctr(&rng->aes_ctx, length_octets, &nc_off,
                                          rng->nonce._8, block, buffer, buffer);
    memcpy(buffer, block, length_octets);
    explicit_bzero(block, 16);
    explicit_bzero(temp, 16);
    return !res;
}

static bool new_key_and_nonce(EPCSPRNG *rng) {
    uint8_t new_octets[32];
    explicit_bzero(new_octets, 32);

    bool ok = fill_blocks(new_octets, 32, rng);

    ok = ok && !mbedtls_aes_setkey_enc(&rng->aes_ctx, new_octets, 128);
    memcpy(rng->nonce._8, new_octets + 16, 16);

    explicit_bzero(new_octets, 32);

    return ok;
}

static bool new_nonce(EPCSPRNG *rng) {
    uint8_t new_octets[16];
    explicit_bzero(new_octets, 16);

    bool ok = fill_blocks(new_octets, 16, rng);
    memcpy(rng->nonce._8, new_octets, 16);

    explicit_bzero(new_octets, 16);

    return ok;
}

#if UINT32_MAX > SIZE_MAX
#error SIZE_MAX must be >= UINT32_MAX
#endif

static const size_t CTR_MAX_OCTETS_PER_NONCE = ((size_t)(1) << 28) / 16;

#ifdef DEBUG
static bool epcsprng_fill_actual
#else
bool epcsprng_fill
#endif
(uint8_t *const buffer, size_t const buflen_octets,
                   EPCSPRNG *const rng) {
    const size_t blocksize = 16;
    bool ok = true;
    const size_t num_max_octet_fills = buflen_octets / CTR_MAX_OCTETS_PER_NONCE;
    uint8_t *bufptr = buffer + 0;

    // how often we have to refresh the nonce as we're limited to <=
    // CTR_MAX_OCTETS_PER_NONCE block encryptions by it.
    for (size_t i = 0; i < num_max_octet_fills;
         ++i, bufptr += CTR_MAX_OCTETS_PER_NONCE) {
        ok = ok && fill_blocks(bufptr, CTR_MAX_OCTETS_PER_NONCE, rng);
        ok = ok && new_nonce(rng);
    }

    if (!ok) {
        return ok;
    }

    //FIXME issue must be between this...

    // fill remaining full blocks
    size_t const num_full_blocks =
        (buflen_octets % CTR_MAX_OCTETS_PER_NONCE) / blocksize;
    if (num_full_blocks) {
        ok = ok && fill_blocks(bufptr, num_full_blocks * blocksize, rng);
        ok = ok && new_nonce(rng);
        bufptr += num_full_blocks * blocksize;
    }

    if (!ok) {
        return ok;
    }

    // sort of the same nonce renewal logic as above.
    if (buflen_octets % blocksize) {
        ok = ok && fill_partial_block(bufptr, buflen_octets % blocksize, rng);
        ok = ok && new_nonce(rng);
    }

    //FIXME... and that

    ok = ok && new_key_and_nonce(rng);

    return ok;
}
#ifdef DEBUG
#define epcsprng_fill(buf, len, rng) \
    fprintf(stderr, "%s:%d: %s, %s, %s\n", __FILE__, __LINE__, #buf, #len, #rng); \
    epcsprng_fill_actual(buf, len, rng);
#endif

struct ThreadedRngCtx {
    mtx_t *write_mutex;
    size_t buflen_octets;
    uint8_t *bufptr;
    EPCSPRNG *rng;
};

static int threaded_fill(void *typepunned_ctx) {
    struct ThreadedRngCtx *ctx = (struct ThreadedRngCtx *)typepunned_ctx;
    const bool ok = epcsprng_fill(ctx->bufptr, ctx->buflen_octets, ctx->rng);

    return (ok) ? thrd_success : thrd_error;
}

size_t per_thread_buflen(size_t const num_octets_total,
                         size_t const blocksize_octets,
                         size_t const num_threads) {
    size_t const per_thread_non_quantized = num_octets_total / num_threads;
    size_t const per_thread_quantized =
        (per_thread_non_quantized / blocksize_octets);

    return per_thread_quantized * blocksize_octets;
}

bool epcsprng_fill_mt(uint8_t *const buffer, size_t const buflen_octets,
                      EPCSPRNG *const rng, size_t const n_parallel) {
    if (SIZE_MAX / sizeof(EPCSPRNG) < n_parallel ||
        SIZE_MAX / 32 < n_parallel) {
        return false;
    }

    // create buffer buffer_mutex
    mtx_t buffer_mutex;
    if (thrd_success != mtx_init(&buffer_mutex, mtx_plain)) {
        return false;
    }

    bool ok = true;
    const size_t blocksize = 16;

    struct ThreadedRngCtx *thread_ctxs =
        malloc(n_parallel * sizeof(struct ThreadedRngCtx));

    thrd_t *threads = malloc(n_parallel * sizeof(thrd_t));

    int *thread_results = malloc(n_parallel * sizeof(int));

    EPCSPRNG *rngs = malloc(n_parallel * sizeof(EPCSPRNG));
    uint8_t *keys_and_nonces = malloc(n_parallel * 32);

    all_not_null(goto mt_fill_cleanup;, thread_ctxs, threads, thread_results,
                                      rngs, keys_and_nonces) {}
    epcsprng_fill(keys_and_nonces, 32 * n_parallel, rng);

    for (size_t i = 0; i < n_parallel; ++i) {
        memcpy(rngs[i].nonce._8, keys_and_nonces + 16 * i, 16);
        mbedtls_aes_init(&rngs[i].aes_ctx);
        if (mbedtls_aes_setkey_enc(&rngs[i].aes_ctx,
                                   keys_and_nonces + n_parallel * 16 + i * 16,
                                   128)) {
            ok = false;
            goto mt_fill_cleanup;
        }
    }

    size_t const octets_per_thread =
        per_thread_buflen(buflen_octets, blocksize, n_parallel);

    for (size_t i = 0; i < n_parallel; ++i) {
        thread_ctxs[i].write_mutex = &buffer_mutex;
        thread_ctxs[i].buflen_octets = octets_per_thread;
        // in case that buflen_octets isn't divisible by (n_parallel *
        // blocksize)
        if (i == (n_parallel - 1)) {
            thread_ctxs[i].buflen_octets =
                buflen_octets - ((n_parallel - 1) * octets_per_thread);
        }
        thread_ctxs[i].bufptr = buffer + i * octets_per_thread;
        thread_ctxs[i].rng = &rngs[i];
    }

    for (size_t i = 0; i < n_parallel; ++i) {
        // if a thread fails to create, then...
        thread_results[i] =
            thrd_create(&threads[i], threaded_fill, (void *)(&thread_ctxs[i]));
        ok = ok && (thrd_success == thread_results[i]);
    }

    //...reading the thread_results[i] would yield uninitialized garbage without
    // the above loop's assignment
    for (size_t i = 0; i < n_parallel; ++i) {
        thrd_join(threads[i], &thread_results[i]);
        ok = ok && (thrd_success == thread_results[i]);
    }

    new_nonce(rng);

mt_fill_cleanup:
    mtx_destroy(&buffer_mutex);
    if (NULL != thread_ctxs) {
        for (size_t i = 0; i < n_parallel; ++i) {
        }
        free(thread_ctxs);
    }
    if (NULL != threads) {
        free(threads);
    }
    if (NULL != thread_results) {
        free(thread_results);
    }
    if (NULL != rngs) {
        for (size_t i = 0; i < n_parallel; ++i) {
            mbedtls_aes_free(&rngs[i].aes_ctx);
        }
        explicit_bzero(rngs, n_parallel * sizeof(EPCSPRNG));
        free(rngs);
    }
    if (NULL != keys_and_nonces) {
        explicit_bzero(keys_and_nonces, n_parallel * 32);
        free(keys_and_nonces);
    }
    return ok;
}
