#pragma once
#include <cmdline.h>

int FileMode(Cmdline_t* cmd);
int StdinMode(Cmdline_t* cmd);

// this handels global init and deinit
static inline int callq_mode(Cmdline_t* cmd)
{
  int retval = 0;
  if (cmd->FilesLen > 0) retval = FileMode(cmd);
  else retval = StdinMode(cmd);

  return retval;
}
