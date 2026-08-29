#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <json-c/json.h>
#include <json-c/json_pointer.h>
#include <json-c/json_object.h>

#include "switch.h"
#include "switch_utils.h"
#include "switch_generate.h"




int main(int argc, char **argv)
{
    // data buffers
    json_object *tokens = NULL;
    char *data = NULL;
    FILE *fd = NULL;
    size_t num_bytes = 0;  // allow getdelim() to allocate buffer with required bytes

    // error flags
    enum json_tokener_error json_error = json_tokener_success;
    bool read_failed = false;
    int rc = EXIT_SUCCESS;
    ssize_t num_chars = 0;

    // open file for reading, obtained by argument or hardcoded
    const char *file = (argc > 1) ? argv[1] : "openconfig-interfaces-data.json";
    fd = fopen(file, "r");
    if(!fd)
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: fopen(%s) error_num:%d error_str:%s\n", __FILE__, __LINE__, __func__, file, errno, strerror(errno));
        rc = EXIT_FAILURE;
        goto cleanup;
    }

    // create string from file and check for errors
    num_chars = getdelim(&data, &num_bytes, '\0', fd);
    read_failed = (num_chars < 0 && ferror(fd)) ? true : false;

    fclose(fd);
    fd = NULL;

    if(num_chars < 0)
    {
        if(read_failed)
        {
            fprintf(stderr, "[ERROR] %s(%d) %s: getdelim() error_num:%d error_str:%s\n", __FILE__, __LINE__, __func__, errno, strerror(errno));
        }
        else
        {
            fprintf(stderr, "[ERROR] %s(%d) %s: file: %s is empty\n", __FILE__, __LINE__, __func__, file);
        }

        rc = EXIT_FAILURE;
        goto cleanup;
    }

    // tokenize string
    tokens = json_tokener_parse_verbose(data, &json_error);
    if(!tokens)
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: json_tokener_parse_verbose() error_desc:%s\n", __FILE__, __LINE__, __func__, json_tokener_error_desc(json_error));
        rc = EXIT_FAILURE;
        goto cleanup;
    }

    // parse and output cfg

    // free memory
    cleanup:
    {
        if(tokens)
        {
            json_object_put(tokens);
            tokens = NULL;
        }

        if(data)
        {
            free(data);
            data = NULL;
        }
    }

    return rc;
}




