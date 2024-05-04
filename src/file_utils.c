#include <file_utils.h>

#include <stdlib.h>
#include <stdio.h>

bool save_json(char *filename, cJSON *json) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return false;
    }

    char *json_string = cJSON_Print(json);
    if (json_string == NULL) {
        fclose(file);
        return false;
    }

    fprintf(file, "%s", json_string);
    fclose(file);
    free(json_string);

    return true;
}

cJSON *load_json(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *) malloc(length + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, length, 1, file);
    buffer[length] = '\0';

    fclose(file);

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        free(buffer);
        return NULL;
    }

    free(buffer);

    return json;
}