#include <file_utils.h>

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

bool create_folder(char *folder) {
    int result = mkdir("/home/me/test.txt", 0777);
    return result == 0;
}

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

char **list_files(char *directory, int *count) {
    DIR *dir = opendir(directory);
    if (dir == NULL) {
        return NULL;
    }

    struct dirent *entry;
    int files_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcasecmp(entry->d_name, ".") == 0 || strcasecmp(entry->d_name, "..") == 0) continue;
        files_count++;
    }

    rewinddir(dir);

    char **files = (char **) malloc(files_count * sizeof(char *));
    if (files == NULL) {
        closedir(dir);
        return NULL;
    }

    files_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcasecmp(entry->d_name, ".") == 0 || strcasecmp(entry->d_name, "..") == 0) continue;
        files[files_count] = (char *) malloc(strlen(entry->d_name) + 1);
        if (files[files_count] == NULL) {
            for (int i = 0; i < files_count; i++) {
                free(files[i]);
            }
            free(files);
            closedir(dir);
            return NULL;
        }
        strcpy(files[files_count], entry->d_name);
        files_count++;
    }

    closedir(dir);

    *count = files_count;

    return files;
}