#include <cmdline.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <runtime/defc.h>

static inline void add_single_arg(Cmdline_t* cmd, const char** argv, const CmdlineOpts_t opt)
{
  cmd->Opts[cmd->OptsLen].Opt = opt;
  cmd->Opts[cmd->OptsLen].has_str = false;
  ++cmd->OptsLen;
}

static inline int add_double_arg(Cmdline_t* cmd, const char** argv, int* i, const int argc, const CmdlineOpts_t opt)
{
  *i = *i + 1;
  if (*i >= argc)
  {
    lerror("Missing argument for `%s`", argv[*i - 1]);
    return 1;
  }
  if (strlen(argv[*i]) >= OPTS_STR_LIMIT)
  {
    lerror("Argument too large! Per argument max is %d chars", OPTS_STR_LIMIT);
    return RET_ERR;
  }

  cmd->Opts[cmd->OptsLen].Opt = opt;
  cmd->Opts[cmd->OptsLen].has_str = true;
  strcpy(cmd->Opts[cmd->OptsLen].OptsStr, argv[*i]);
  ++cmd->OptsLen;

  return RET_OK;
}

int MakeCmdline(Cmdline_t *cmd, const int argc, const char** argv)
{
  if (cmd == NULL) return 1;

  cmd->FilesLen = 0;
  cmd->OptsLen = 0;

  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-')
    {
      if (cmd->OptsLen >= OPTS_LIMIT) goto TOO_MANY_ARGS;

      if (strcmp(argv[i], "--help") == 0) add_single_arg(cmd, argv, Help);
      else if (strcmp(argv[i], "--version") == 0) add_single_arg(cmd, argv, Version);
      else if (strcmp(argv[i], "--define") == 0) { if (add_double_arg(cmd, argv, &i, argc, Define)) return 1; }
      else
      {
        lerror("Undefined arg `%s`", argv[i]);
        return RET_ERR;
      }
    }
    else
    {
      if (cmd->FilesLen >= FILES_LIMIT) goto TOO_MANY_ARGS;
      if (strlen(argv[i]) >= PER_FILE_LIMIT) goto ARG_TOO_LARGE;
      strcpy(cmd->Files[cmd->FilesLen], argv[i]);
      ++cmd->FilesLen;
    }
  }

  return RET_OK;
TOO_MANY_ARGS:
  lerror("Too many command line arguments! max limit reached");
  return RET_ERR;
ARG_TOO_LARGE:
  lerror("Argument too large! Per argument max is %d chars", PER_FILE_LIMIT);
  return RET_ERR;
}
