#include "../include/epcsprng.h"
#include <stdio.h>
#include <stdlib.h>

struct KAT {
    const size_t buflen_octets;
    const size_t num_threads;
    const size_t blocksize;
    const size_t per_thread_shall;
};

#if ((SIZE_MAX)>>32) == 0
#error SIZE_MAX is too small, please upgrade from your Z80.
#endif

static const struct KAT kats[] =
{
    {
        .buflen_octets = (size_t)(1) << 32,
        .num_threads = (size_t)(1) << 4,
        .blocksize = (size_t)(1) << 4,
        .per_thread_shall = (size_t)(1) << (32 - 4)
    },
    {
        .buflen_octets = ((size_t)(1) << 32)+15,
        .num_threads = (size_t)(1) << 3,
        .blocksize = (size_t)(1) << 4,
        .per_thread_shall = (size_t)(1) << (32 - 3)
    },
};


int main(void) {
    const size_t num_kats = sizeof(kats)/sizeof(kats[0]);
    for(size_t i=0; i<num_kats;++i) {
        const size_t is = per_thread_buflen(kats[i].buflen_octets, kats[i].blocksize, kats[i].num_threads);
        if(kats[i].per_thread_shall != is) {
            flockfile(stderr);
            fprintf(stderr, "Failed KAT # %zu:\n", i);
            fprintf(stderr, "\tshall: %zu\n", kats[i].per_thread_shall);
            fprintf(stderr, "\tis   : %zu\n", is);
            fflush(stderr);
            funlockfile(stderr);
            exit(EXIT_FAILURE);
        }
    }
}
