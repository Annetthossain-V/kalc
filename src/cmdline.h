#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define PER_FILE_LIMIT 255
#define FILES_LIMIT 48
#define OPTS_LIMIT 64
#define OPTS_STR_LIMIT 255

enum CmdlineOpts {
  Help,
  Version,
  Define,
};
typedef enum CmdlineOpts CmdlineOpts_t;

// not using dynamic memory because
// of safety and speed.
// A lot of memory is wasted.
struct Cmdline {
  char Files[PER_FILE_LIMIT][FILES_LIMIT];
  struct Opts {
    CmdlineOpts_t Opt;
    char OptsStr[OPTS_STR_LIMIT];
    bool has_str;
  } Opts[OPTS_LIMIT];
  uint16_t FilesLen;
  uint8_t OptsLen;
};
typedef struct Cmdline Cmdline_t;

int MakeCmdline(Cmdline_t* cmd, const int argc, const char** argv);

static inline int CmdlineContainsSingle(const Cmdline_t* cmd, const CmdlineOpts_t opt)
{
  for (uint8_t i = 0; i < cmd->OptsLen; ++i)
    if (cmd->Opts[i].Opt == opt) return true;
  return false;
}

static inline void PrintHelp()
{
  printf("Usage: kalc <options> <files>\n");
  printf("Options: \n");
  printf(" --version # prints version number\n");
  printf(" --help # prints this message\n");
  printf(" --define <definition=value> # define a value\n");
}
