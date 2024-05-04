#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include <cJSON.h>

bool save_json(char *filename, cJSON *json);

cJSON* load_json(char *filename);

#endif //FILE_UTILS_H
