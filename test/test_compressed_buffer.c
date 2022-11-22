#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <zstd.h>

#include "../include/epcsprng.h"

#include "utils.c"

int main(int argc, char* argv[]) {
    size_t num_threads = (argc>1) ? (size_t)(atoi(argv[argc-1])) : 1;
    const int num_iters = 10;
    const double max_compress = 0.99;
    const size_t buflen_octets = ((size_t)(1) << 28);
    const size_t compressed_buffer_len = ZSTD_compressBound(buflen_octets);

    uint8_t *buffer = malloc(buflen_octets);
    memset(buffer, 0, buflen_octets);
    uint8_t *compressed_buffer = malloc(compressed_buffer_len);
    EPCSPRNG *rng = epcsprng_new_auto_key();

    if (!(SIZE_MAX >> 31) || NULL == buffer || NULL == compressed_buffer ||
        NULL == rng) {
        exit(EXIT_FAILURE);
    }

    printf("# threads: %zu\n", num_threads);

    for (int i = 0; i < num_iters; ++i) {
        printf("iteration %d\r", i+1);
        fflush(stdout);
        const bool ok = epcsprng_fill_mt(buffer, buflen_octets, rng, num_threads);
        if (!ok) {
            fprintf(stderr, "failed to fill on iteration %d\n", i);
            exit(EXIT_FAILURE);
        }
        size_t compressed_size = ZSTD_compress(
            compressed_buffer, compressed_buffer_len, buffer, buflen_octets, 9);
        double compression_ratio =
            (double)(compressed_size) / (double)(buflen_octets);
        if (compression_ratio < max_compress) {
            fprintf(stderr, "bad fill on iteration %d: ratio = %.6f\n", i,
                    compression_ratio);
            dump_rle_buffer(buffer, buflen_octets);
            exit(EXIT_FAILURE);
        }
    }

    free(buffer);
    free(compressed_buffer);
    free(rng);
}
