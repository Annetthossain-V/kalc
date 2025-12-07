#include <runtime/defc.h>
#include <stdlib.h>
#include <cmdline.h>
#include <stdio.h>
#include <mode.h>

#define VERSION 0.1

static inline int check_version_or_help(Cmdline_t* cmd)
{
  if (CmdlineContainsSingle(cmd, Version))
  {
    linfo("Version %.2f", VERSION);
    return RET_OK;
  }
  else if (CmdlineContainsSingle(cmd, Help))
  {
    PrintHelp();
    return RET_OK;
  }
  return RET_ERR;
}

int main(const int argc, const char** argv)
{
  SetFileLog(stdout); // make this dynamic

  Cmdline_t* cmd = (Cmdline_t*) malloc(sizeof(Cmdline_t));
  if (MakeCmdline(cmd, argc, argv) != RET_OK) goto ERR;
  if (check_version_or_help(cmd) == RET_OK) goto fini;
  if (callq_mode(cmd) != RET_OK) goto ERR;

fini:
  free(cmd);
  return !RET_OK;

ERR:
  free(cmd);
  return !RET_ERR;
}
