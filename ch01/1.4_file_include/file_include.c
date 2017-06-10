#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 1024

/**
 * error no
 */
static int _last_errno = 0;

/**
 * error message
 */
static char *_last_error = NULL;

/**
 * output buffer size
 */
static size_t output_size = MAX_LINE_SIZE * 8;


static void print_last_error(void);
static bool file_exists(const char *file_name);
static bool include_parser(const char *input_file, const char *output_file);
static char *parse_include_file(const char *input_file);
static size_t file_get_size(FILE *fp);
static bool string_concat(char *dst, const char *source, size_t dst_length);


int main(int argc, char *argv[]) {
    if (argc < 3) {
        // Command line format error, print usage to user.
        fprintf(stderr, "Usage: %s [output.file] [entry.file]\n", argv[0]);
        exit(0);
    }

    // output/input file name [C++11]
    const char *output_file = argv[1];
    const char *input_file = argv[2];

    // check entry.file exists
    if (file_exists(input_file) == false) {
        print_last_error();
    }

    // parse entry.file
    if (include_parser(input_file, output_file) == false) {
        print_last_error();
    }

    return 0;
}

/**
 * print last error and exit
 */
static void print_last_error(void) {
    fprintf(stderr, "%#08X: %s\n", _last_errno, _last_error);
    exit(_last_errno);
}

/**
 * check file exists, return `true` if file exist, either return `false`
 *
 * @param file_name
 * @return bool
 */
static bool file_exists(const char *file_name) {
    FILE *fp = NULL;

    // try to open file
    if ((fp = fopen(file_name, "r")) == NULL) {
        // set error message and number
        _last_errno = 1;
        _last_error = "file not found";
        // open file error occurs
        return false;
    }
    // open file success
    fclose(fp);
    return true;
}

/**
 * parse entry file
 *
 * @param input_file
 * @param output_file
 * @return bool
 */
static bool include_parser(const char *input_file, const char *output_file) {
    FILE *output_fp = NULL;
    if ((output_fp = fopen(output_file, "w")) == NULL) {
        _last_errno = 4;
        _last_error = "open output file fail";
        return false;
    }

    // parse entry file
    char *output_string = parse_include_file(input_file);
    if (output_string == NULL) {
        return false;
    }
    // write to file
    fwrite(output_string, sizeof(char), strlen(output_string), output_fp);

    // close file handler
    fclose(output_fp);
    free(output_string);

    return true;
}

static char *parse_include_file(const char *input_file) {
    FILE *input_fp = NULL;
    if ((input_fp = fopen(input_file, "r")) == NULL) {
        _last_errno = 2;
        _last_error = "open input file fail";
        return false;
    }

    // foreach all lines
    output_size = file_get_size(input_fp) * 2;
    char *output_string = (char*)malloc(output_size);
    memset(output_string, 0, output_size);

    char left_text[MAX_LINE_SIZE] = { 0 };
    char right_text[MAX_LINE_SIZE] = { 0 };

    // foreach all line
    for (char current_line[MAX_LINE_SIZE] = { 0 }; fgets(current_line, 1024, input_fp) != NULL; ) {
        sscanf(current_line, "%s %s", left_text, right_text);
        // format like `include xxx`
        if (strcmp(left_text, "include") == 0 && strlen(right_text) != 0) {
            // non allow include self
            if (strcmp(right_text, input_file) == 0) {
                // free output buffer
                free(output_string);
                // error message
                _last_errno = 16;
                _last_error = "not allow include self";
                return NULL;
            }
            // parse all contents
            char *file_contents = parse_include_file(right_text);
            // content error
            if (file_contents == NULL) {
                // free output buffer
                free(output_string);

                return NULL;
            }
            // concat string
            if (string_concat(output_string, file_contents, strlen(file_contents)) == false) {
                // free output buffer
                free(output_string);

                return NULL;
            }
            // close buffer and file handler
            free(file_contents);
        } else {
            // concat current line contents
            if (string_concat(output_string, current_line, output_size) == false) {
                // free output buffer
                free(output_string);

                return NULL;
            }
        }
        // reset buffer
        memset(current_line, 0, MAX_LINE_SIZE);
        memset(left_text, 0, MAX_LINE_SIZE);
        memset(right_text, 0, MAX_LINE_SIZE);
    }

    // close file handler
    fclose(input_fp);

    return output_string;
}

/**
 * get file size
 *
 * @param fp
 * @return
 */
static size_t file_get_size(FILE *fp) {
    int current_position = ftell(fp);
    // end of file
    fseek(fp, 0, SEEK_END);
    // get size
    size_t file_size = (size_t)ftell(fp);
    // return origin
    fseek(fp, current_position, SEEK_SET);
    // return size
    return file_size;
}

/**
 * concat string to dst
 *
 * @param dst
 * @param source
 * @param dst_length
 * @return
 */
static bool string_concat(char *dst, const char *source, size_t dst_length) {
    while (dst_length - strlen(source) - 1 < 0) {
        // re-calloc mem
        if ((dst = realloc(dst, dst_length * 2)) == NULL) {
            _last_errno = 4;
            _last_error = "realloc error occurs";
            return false;
        }
        // reset output size
        output_size *= 2;
    }
    // concat string
    strncat(dst, source, strlen(source));
    return true;
}
