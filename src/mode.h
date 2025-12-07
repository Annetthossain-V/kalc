#pragma once
#include <cmdline.h>
#include <runtime/core.h>
#include <runtime/defc.h>

int FileMode(Cmdline_t* cmd);
int StdinMode(Cmdline_t* cmd);

// this handels global init and deinit
// only must be called once
static inline int callq_mode(Cmdline_t* cmd)
{
  int retval = RET_OK;
  if (__init_global() != RET_OK) return RET_ERR;

  if (cmd->FilesLen > 0) retval = FileMode(cmd);
  else retval = StdinMode(cmd);

  if (__fini_global() != RET_OK) return RET_ERR;
  return retval;
}
