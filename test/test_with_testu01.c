#include <bbattery.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/epcsprng.h"

#define BUF_SIZE ((size_t)1 << 28)

static EPCSPRNG *rng_ctx;
static uint32_t *buffer;
static size_t bufpos = BUF_SIZE;
static uint64_t fill_call_count = 0;

static inline uint32_t epcsprng_wrapper_actual(void) {
    if (bufpos < BUF_SIZE) {
        return buffer[bufpos++];
    } else {
        fill_call_count++;
        epcsprng_fill_mt((uint8_t*)buffer, BUF_SIZE * sizeof(uint32_t), rng_ctx, 4);
        bufpos = 0;
        return buffer[bufpos++];
    }
}

int main(void) {
    rng_ctx = epcsprng_new_auto_key();
    buffer = malloc(BUF_SIZE * sizeof(uint32_t));

    if(!(SIZE_MAX >> 30)) {
        fprintf(stderr, "your OS size_t is too small.\n");
    }

    if(NULL == buffer || NULL == rng_ctx) {
        fprintf(stderr, "Failed to allocate memory or epcsprng.\n");
        exit(EXIT_FAILURE);
    }

    unif01_Gen *epcsprng_wrapper =
        unif01_CreateExternGenBits("epcsprng", epcsprng_wrapper_actual);

    bbattery_FIPS_140_2(epcsprng_wrapper);
    printf("### called fill %" PRIu64 " times ###\n", fill_call_count);
    fill_call_count = 0;

    bbattery_SmallCrush(epcsprng_wrapper);
    printf("### called fill %" PRIu64 " times ###\n", fill_call_count);
    fill_call_count = 0;

    bbattery_BigCrush(epcsprng_wrapper);

    printf("### called fill %" PRIu64 " times ###\n", fill_call_count);

    free(buffer);
    epcsprng_destroy(rng_ctx);
}
