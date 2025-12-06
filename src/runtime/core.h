#pragma once
#include <stdio.h>

extern FILE* file_log;

int __init_global(void);
int __fini_global(void);

void VariableMutexLock(void);
void VariableMutexUnlock(void);
