#ifndef TIME_H
#define TIME_H

#include <stdbool.h>

#define TARGET_FPS 60
#define FRAME_DURATION_MS (1000 / TARGET_FPS)

void start_frame();

void end_frame();

#endif //TIME_H
