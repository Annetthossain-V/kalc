#include <runtime/core.h>
#include <pthread.h>
#include <stdio.h>

FILE* file_log = NULL;

static pthread_mutex_t VariableMutex;


int __init_global(void)
{
  if (pthread_mutex_init(&VariableMutex, NULL) != 0) return 0;

  return 1;
}

int __fini_global(void)
{
  if (pthread_mutex_destroy(&VariableMutex) != 0) return 0;  

  return 1;
}

void VariableMutexLock(void) { pthread_mutex_lock(&VariableMutex); }
void VariableMutexUnlock(void) { pthread_mutex_unlock(&VariableMutex); }
