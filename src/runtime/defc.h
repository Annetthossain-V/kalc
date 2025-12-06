#pragma once
#include <stdio.h>
#include <runtime/core.h>

#define RET_OK 0x1 
#define RET_ERR 0x0

static inline void SetFileLog(FILE* fp) { file_log = fp; }

#define lerror(x, ...) \
    fprintf(file_log, "\x1b[31m[ERR][%s(%d): int %s()] \x1b[0m" x "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define linfo(x, ...) \
    fprintf(file_log, "\x1b[32m[INFO] \x1b[0m" x "\n", ##__VA_ARGS__)

#ifdef DEBUG 
  #define ldbg(x, ...) \
    fprintf(file_log, "\x1b[33m[DEBUG][%s(%d): int %s()] \x1b[0m" x "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else 
  #define ldbg(x, ...)
#endif
