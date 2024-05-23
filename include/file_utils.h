#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include "../libs/include/cJSON.h"


/**
 * Create a folder
 * @param folder the folder to create
 * @return true if the folder was created successfully, false otherwise
 */
bool create_folder(char *folder);

/**
 * Save a cJSON object to a file
 * @param filename
 * @param json
 * @return true if the file was saved successfully, false otherwise
 */
bool save_json(char *filename, cJSON *json);

/**
 * Load a cJSON object from a file
 * @param filename
 * @return cJSON object or NULL if the file could not be loaded
 */
cJSON* load_json(char *filename);

/**
 * List all files in a directory
 * @param directory
 * @param count a pointer to store the number of files found
 * @return Char[]* array of file names or NULL if the directory could not be opened
 */
char** list_files(char *directory, int *count);

/**
 * Concatenate a directory, file name and extension to create a file path
 * @param directory
 * @param file_name
 * @param extension
 * @return concatenated file path : directory / file_name . extension
 */
char* get_file_path(char* directory, char* file_name, char* extension);

#endif //FILE_UTILS_H
