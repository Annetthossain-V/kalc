#include "runtime/defc.h"
#include <runtime/core.h>

#include <pthread.h>
#include <stdio.h>

FILE* file_log = NULL;

static pthread_mutex_t VariableMutex;
static pthread_mutex_t CodeBuffer; // used for holding blocks to execute

int __init_global(void)
{
  if (pthread_mutex_init(&VariableMutex, NULL) != 0) return 0;
  if (pthread_mutex_init(&CodeBuffer, NULL) != 0) return 0;

  return RET_OK;
}

int __fini_global(void)
{
  if (pthread_mutex_destroy(&VariableMutex) != 0) return 0;
  if (pthread_mutex_destroy(&CodeBuffer) != 0) return 0;

  return RET_OK;
}

void VariableMutexLock(void) { pthread_mutex_lock(&VariableMutex); }
void VariableMutexUnlock(void) { pthread_mutex_unlock(&VariableMutex); }

void CodeBufferLock(void) { pthread_mutex_lock(&CodeBuffer); }
void CodeBufferUnlock(void) { pthread_mutex_unlock(&CodeBuffer); }
