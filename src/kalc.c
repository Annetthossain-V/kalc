#include <stdlib.h>
#include <cmdline.h>
#include <stdio.h>
#include <mode.h>

#define VERSION 0.1

static inline int check_version_or_help(Cmdline_t* cmd)
{
  if (CmdlineContainsSingle(cmd, Version))
  {
    printf("Version %.2f", VERSION);
    return 1;
  }
  else if (CmdlineContainsSingle(cmd, Help))
  {
    PrintHelp();
    return 1;
  }
  return 0;
}

int main(const int argc, const char** argv)
{
  Cmdline_t* cmd = (Cmdline_t*) malloc(sizeof(Cmdline_t));
  if (MakeCmdline(cmd, argc, argv)) goto ERR;
  if (check_version_or_help(cmd)) goto fini;
  if (!callq_mode(cmd)) goto ERR;

fini:
  free(cmd);
  return 0x000;

ERR:
  free(cmd);
  return 0x001;
}
