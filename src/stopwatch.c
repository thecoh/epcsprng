#include "../include/stopwatch.h"

#include <time.h>

#define CLOCK_IN_USE CLOCK_MONOTONIC

static inline int64_t spec2stamp_ns(struct timespec const *const ts) {
    return INT64_C(1000000000) * ts->tv_sec + ts->tv_nsec;
}

void stopwatch_start(Stopwatch*const sw) {
    clock_gettime(CLOCK_IN_USE, &sw->begin);
}

int64_t stopwatch_stop(Stopwatch*const sw) {
    struct timespec end;
    clock_gettime(CLOCK_IN_USE, &end);
    const int64_t elapsed = (spec2stamp_ns(&end) - spec2stamp_ns(&sw->begin));
    sw->total_elapsed_ns += elapsed;
    return elapsed;
}

int64_t stopwatch_total_ns(Stopwatch const*const sw ) {
    return sw->total_elapsed_ns;
}
