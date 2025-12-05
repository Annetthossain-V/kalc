#include <stdint.h>
#include <stddef.h>
#include <mode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser/lexer.h>

static int buff_handler(const char* buff)
{
  size_t lexer_len = 0;
  lexer_t** lexer = LexStr(buff, &lexer_len);
  if (lexer == NULL) return 1;

  LexFree(lexer, lexer_len);
  return 0;
}

int FileMode(Cmdline_t* cmd)
{
  char* buff = (char*) malloc(1024);
  for (uint16_t i = 0; i < cmd->FilesLen; ++i)
  {
    FILE* file = fopen(cmd->Files[i], "r");
    if (file == NULL)
    {
      fprintf(stderr, "[ERR] Unable to open file `%s`\n", cmd->Files[i]);
      free(buff);
      return 0;
    }

    while (fgets(buff, 1024, file))
    {
      buff[strlen(buff) - 1] = '\0';
      if (strcmp(buff, "exit") == 0)
      {
        fclose(file);
        goto fini;
      }

      if (buff_handler(buff) != 0)
      {
        free(buff);
        fclose(file);
        return 0;
      }
    }

    fclose(file);
  }

fini:
  free(buff);
  return 1;
}

int StdinMode(Cmdline_t* cmd)
{
  char* buff = (char*)malloc(1024);
  for (;;)
  {
    putchar('$');
    putchar(' ');

    fgets(buff, 1024, stdin);
    buff[strlen(buff) - 1] = '\0';
    if (strcmp(buff, "exit") == 0) break;

    if (buff_handler(buff) != 0)
    {
      free(buff);
      return 0;
    }
  }

  free(buff);
  return 1;
}
