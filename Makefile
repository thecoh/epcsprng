CC?=clang
#-Rpass-missed
#-fsanitize=undefined,memory,cfi-cast-strict 
CFLAGS := -O3 -fno-omit-frame-pointer -march=native -mtune=native \
		  -Wno-declaration-after-statement \
		  -g3 -fverbose-asm -UDEBUG \
		  -fPIC -D_FORTIFY_SOURCE=2 -fstack-protector-all -fcf-protection=full -fstack-clash-protection
		  
LDFLAGS := -lmbedcrypto -fuse-ld=mold -Wl,-z,now

# Do not use the annobin clang plugin as this will cause **any** compilation to fail on Fedora 37.

ifeq "$(CC)" "clang"
	CFLAGS += -Weverything -flto=thin -frecord-command-line -Wthread-safety
else
	CFLAGS += -Wextra -flto -fplugin=annobin -frecord-gcc-switches -fharden-compares
endif

OBJS := build/epcsprng.o \
	    build/stopwatch.o
LIBB3_OBJS := build/test/blake3_sse2.o \
			  build/test/blake3_sse41.o \
			  build/test/blake3_avx2.o \
			  build/test/blake3_avx512.o

libepcsprng.so: $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)

libb3.so:
	$(CC) $(CFLAGS) -w -msse2   test/BLAKE3/c/blake3_sse2.c  -c -o build/test/blake3_sse2.o
	$(CC) $(CFLAGS) -w -msse4.1 test/BLAKE3/c/blake3_sse41.c -c -o build/test/blake3_sse41.o
	$(CC) $(CFLAGS) -w -mavx2   test/BLAKE3/c/blake3_avx2.c  -c -o build/test/blake3_avx2.o
	$(CC) $(CFLAGS) -w -mavx512f -mavx512vl test/BLAKE3/c/blake3_avx512.c  -c -o build/test/blake3_avx512.o
	$(CC) $(CFLAGS) -w -shared -o $@ test/BLAKE3/c/blake3.c test/BLAKE3/c/blake3_dispatch.c test/BLAKE3/c/blake3_portable.c $(LIBB3_OBJS) $(LDFLAGS)

shim.so: shim.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -std=gnu11 -fsanitize= -shared -o $@ $^ -ldl -lmbedcrypto

bench: libepcsprng.so libb3.so
	$(CC) $(CFLAGS) -fPIE -o bench test/bench.c -L. -lepcsprng -lb3 $(LDFLAGS)

test_u01: libepcsprng.so
	$(CC) $(CFLAGS) -fPIE -o test_u01 test/test_with_testu01.c $(LDFLAGS) -ltestu01 -L. -lepcsprng

test_compression: libepcsprng.so
	$(CC) $(CFLAGS) -fPIE -o test_compression test/test_compressed_buffer.c $(LDFLAGS) -L. -lepcsprng -lzstd

test_per_thread_buflen: libepcsprng.so
	$(CC) $(CFLAGS) -fPIE -o $@ test/test_per_thread_buflen.c $(LDFLAGS) -L. -lepcsprng

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJS) libepcsprng.so libb3.so bench test_u01 test_compression pairs

.PHONY: clean
