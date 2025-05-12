#include <stdio.h>

// 4klang export uses these symbols
extern void _4klang_render(void*);
extern int _4klang_current_tick;

#define SAMPLE_RATE 44100
#define BPM 140
#define PATTERN_SIZE_SHIFT 5
#define PATTERN_SIZE (1 << PATTERN_SIZE_SHIFT)
#define MAX_PATTERNS 18
#define MAX_TICKS (PATTERN_SIZE * MAX_PATTERNS)
#define SAMPLES_PER_TICK (SAMPLE_RATE * 4 * 60 / (BPM * 16))
#define MAX_SAMPLES (MAX_TICKS * SAMPLES_PER_TICK)

float buffer[SAMPLES_PER_TICK * 2];

int main() {
    FILE *f = fopen("output.raw", "wb");
    _4klang_current_tick = 0;

    for (int i = 0; i < MAX_TICKS; i++) {
        _4klang_render(buffer);
        fwrite(buffer, sizeof(buffer), 1, f);
    }

    fclose(f);
    return 0;
}
