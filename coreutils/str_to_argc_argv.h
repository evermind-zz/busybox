#ifndef str_to_argc_argv_h
#include <string.h>
#include <stdbool.h>

/*
    in args         the string to parse
    in buf          a zero-initialized buffer with size "strlen(args) + 1" or greater
    out argc        arguments count
    out argv        a char* array buffer
    argvlen         argv array size
*/
void str_to_argc_argv(const char *args, char *buf, int *argc, char **argv, int argvlen) {
    enum PARSER_STATE {
        GET_CHAR,
        SEEK_DOUBLE_QUOTE_END,
        SEEK_SINGLE_QUOTE_END,

    } parser_state = GET_CHAR;

    size_t commit = 0;//character commit (from "args" into "buf") count
    for (size_t c = 0; c < strlen(args); c++) {
        switch (parser_state) {
        case GET_CHAR: {
            switch (args[c]) {
            case ' ':
            case '\t': {
                if (commit != 0 && buf[commit - 1] != '\0') {//ignore leading whitespaces
                    buf[commit++] = '\0';
                }
                break;
            }
            case '"': {
                parser_state = SEEK_DOUBLE_QUOTE_END;
                break;
            }
            case '\'': {
                parser_state = SEEK_SINGLE_QUOTE_END;
                break;
            }
            default: {
                buf[commit++] = args[c];
                break;
            }
            }
            break;
        }
        case SEEK_DOUBLE_QUOTE_END: {
            switch (args[c]) {
            case '"': {
                bool escaped = args[c - 1] == '\\' && args[c - 2] != '\\';//safe (c can't be less than 2 here)
                if (!escaped) {
                    parser_state = GET_CHAR;
                }
                else {
                    buf[commit++] = '"';
                }
                break;
            }
            default: {
                buf[commit++] = args[c];
                break;
            }
            }
            break;
        }
        case SEEK_SINGLE_QUOTE_END: {
            switch (args[c]) {
            case '\'': {
                parser_state = GET_CHAR;
                break;
            }
            default: {
                buf[commit++] = args[c];
                break;
            }
            }
            break;
        }
        }
    }

    int argc_ = 0;
    while (*buf != '\0' && argc_ < argvlen) {
        *(argv + argc_++) = buf;
        buf += strlen(buf) + 1;
    }
    *argc = argc_;
}
#define str_to_argc_argv_h
#endif
