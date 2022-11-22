#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void dump_rle_buffer(uint8_t const *const buffer, size_t const buflen) {
    const size_t block_size = 16; // octets
    size_t num_small_runs = 0;
    for (size_t pos = 0; pos < buflen; pos += block_size) {
        if (pos < buflen - block_size) {
            size_t run = 0, i = block_size;
            for (; pos + i < buflen - 1; i += block_size) {
                if (0 == memcmp(buffer + pos, buffer + pos + block_size,
                            block_size)) {
                    run++;
                } else
                    break;
            }
            if (run) {
                printf("%zu.B#", run + 1);
                pos += run * block_size;
            } else {
                run = 0;
                i = 0;
                for (; pos + i < buflen - 1; ++i) {
                    if (buffer[pos + i] == buffer[pos + i + 1]) {
                        run++;
                    } else {
                        break;
                    }
                }
                if (run) {
                    num_small_runs++;
                    printf("%zu.%#02" PRIx8 "|", run + 1, buffer[pos]);
                    pos += (i / block_size);
                }
            }
        }
    }
    printf("# small runs = %zu, buflen = %zu octets\n", num_small_runs, buflen);
}
