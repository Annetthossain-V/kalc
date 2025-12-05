#include <stddef.h>
#include <mode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser/lexer.h>

int FileMode(Cmdline_t* cmd)
{

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

    size_t lexer_len = 0;
    lexer_t** lexer = LexStr(buff, &lexer_len);
    if (lexer == NULL)
    {
      free(buff);
      return 0;
    }

    LexFree(lexer, lexer_len);
  }

  free(buff);
  return 1;
}
