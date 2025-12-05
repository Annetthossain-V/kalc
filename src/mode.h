#pragma once
#include <cmdline.h>
#include <runtime/core.h>

int FileMode(Cmdline_t* cmd);
int StdinMode(Cmdline_t* cmd);

// this handels global init and deinit
// only must be called once
static inline int callq_mode(Cmdline_t* cmd)
{
  int retval = 0;
  if (!__init_global()) return 0;

  if (cmd->FilesLen > 0) retval = FileMode(cmd);
  else retval = StdinMode(cmd);

  if (!__fini_global()) return 0;
  return retval;
}
