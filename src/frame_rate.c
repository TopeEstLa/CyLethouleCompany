#include <frame_rate.h>

#include <time.h>
#include <unistd.h>
#include <curses.h>

clock_t start_time;
clock_t end_time;
float elapsed_time;


void start_frame() {
    start_time = clock();
}

void end_frame() {
    end_time = clock();
    elapsed_time = ((float) (end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    if (elapsed_time < FRAME_DURATION_MS) {
        int wait_time = FRAME_DURATION_MS - elapsed_time;

        napms(wait_time);
    } else {
        napms(1);
    }
}