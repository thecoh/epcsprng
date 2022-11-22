#pragma once

#include <stdint.h>
#include <time.h>

typedef struct Stopwatch {
    int64_t total_elapsed_ns;
    struct timespec begin;
} Stopwatch;

void stopwatch_start(Stopwatch*const);
int64_t stopwatch_stop(Stopwatch*const);
int64_t stopwatch_total_ns(Stopwatch const*const);
