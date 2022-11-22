#include "../include/epcsprng.h"
#include "../include/stopwatch.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/random.h>
#include <sys/sysinfo.h>

#include <mbedtls/sha256.h>

#include "./BLAKE3/c/blake3.h"

static void print_hash(uint8_t const *const buffer,
                       size_t const buflen_octets) {
    uint8_t digest[256 / 8];

    blake3_hasher ctx;
    blake3_hasher_init(&ctx);
    blake3_hasher_update(&ctx, buffer, buflen_octets);
    blake3_hasher_finalize(&ctx, digest, 256 / 8);

    printf("# ");
    for (int i = 0; i < 256 / 8; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");
    fflush(stdout);
}

static void bench_single_threaded(size_t const buflen) {
    uint8_t key[16];
    if (getentropy(key, 16)) {
        fprintf(stderr, "failed to create key.\n");
        exit(EXIT_FAILURE);
    }

    EPCSPRNG *rng = epcsprng_new(key, 16);
    if (NULL == rng) {
        fprintf(stderr, "failed to allocate rng.\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *buffer = malloc(buflen);
    if (NULL == buffer) {
        epcsprng_destroy(rng);
        exit(EXIT_FAILURE);
    }

    Stopwatch watch = {0};

    const int num_iters = 25;

    for (int i = 0; i < num_iters; ++i) {
        stopwatch_start(&watch);
        epcsprng_fill(buffer, buflen, rng);
        const int64_t elapsed = stopwatch_stop(&watch);
        printf("%zu;1;%" PRIi64 "\n", buflen, elapsed);
        print_hash(buffer, buflen);
    }

    epcsprng_destroy(rng);
    free(buffer);
}

static void bench_multi_threaded(size_t const buflen, size_t const nprocs) {
    uint8_t key[16];
    if (getentropy(key, 16)) {
        fprintf(stderr, "failed to create key.\n");
        exit(EXIT_FAILURE);
    }

    EPCSPRNG *rng = epcsprng_new(key, 16);
    if (NULL == rng) {
        fprintf(stderr, "failed to allocate rng.\n");
        exit(EXIT_FAILURE);
    }

    uint8_t *buffer = malloc(buflen);
    if (NULL == buffer) {
        epcsprng_destroy(rng);
        exit(EXIT_FAILURE);
    }

    Stopwatch watch = {0};

    const int num_iters = 25;

    for (int i = 0; i < num_iters; ++i) {
        stopwatch_start(&watch);
        epcsprng_fill_mt(buffer, buflen, rng, nprocs);
        const int64_t elapsed = stopwatch_stop(&watch);
        printf("%zu;%zu;%" PRIi64 "\n", buflen, nprocs, elapsed);
        print_hash(buffer, buflen);
    }

    epcsprng_destroy(rng);
    free(buffer);
}

int main(void) {
    const size_t BUF_LEN =
#if 0
        (SIZE_MAX / 2 > UINT32_MAX) ? ((size_t)(UINT32_MAX) + 1) * 3 : SIZE_MAX;
#else
        (size_t)(1) << 33;
#endif

        printf("octets;threads;time(ns)\n");

    bench_single_threaded(BUF_LEN);

#if 1
#if 0
    const size_t nprocs = (size_t)get_nprocs_conf();
    if ((size_t)(-1) == nprocs) {
        exit(EXIT_FAILURE);
    }
#else
    const size_t nprocs = 12; // thanks glibc for messing up that functionality by returning 16 instead.
#endif
    printf("#testing for 2..%zu threads\n", nprocs);
    for (size_t i = 2; i <= nprocs; ++i) {
        bench_multi_threaded(BUF_LEN, i);
    }
#endif
}
