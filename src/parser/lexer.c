#include <parser/lexer.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static inline char* sdub(const char* s, size_t n)
{
  char* r = (char*) malloc(n + 1);
  memcpy(r, s, n);
  r[n] = '\0';
  return r;
}

// not handeling errors for performance
static char** split_by_delims(const char* buff, const char* delims, size_t* count)
{
  if (!buff) return NULL;

  size_t cap = 16;
  size_t _count = 0;
  char** tokens = (char**) malloc(cap * sizeof(char*));
  if (!tokens) return NULL;

  const char* p = buff;
  const char* TokenStart = NULL;
  bool inq = false;

  #define PUSH_TOKEN(tok) do { \
    if (_count + 2 >= cap) { \
      cap += 16; \
      char** tmp = realloc(tokens, cap * sizeof(char*)); \
      tokens = tmp; } \
      tokens[_count++] = (tok); } \
      while (0)

  while (*p)
  {
    unsigned char c = (unsigned char)*p;
    if (inq)
    {
      if (c == '"')
      {
        char* tok = sdub(TokenStart, p - TokenStart);
        PUSH_TOKEN(tok);
        TokenStart = NULL;
        inq = false;
        p++;
      }
      else 
      {
        p++;
      }
      continue;
    }

    if (c == '"')
    {
      if (TokenStart)
      {
        char* tok = sdub(TokenStart, p - TokenStart);
        PUSH_TOKEN(tok);
        TokenStart = NULL;
      }
      inq = true;
      TokenStart = ++p;
      continue;
    }

    if (isspace(c))
    {
      if (TokenStart)
      {
        char* tok = sdub(TokenStart, p - TokenStart);
        PUSH_TOKEN(tok);
        TokenStart = NULL;
      }
      p++;
      continue;
    }

    if (strchr(delims, c))
    {
      if (TokenStart)
      {
        char* tok = sdub(TokenStart, p - TokenStart);
        PUSH_TOKEN(tok);
        TokenStart = NULL;
      }

      char dstr[2] = { *p, '\0'};
      char* delcopy = strdup(dstr);
      PUSH_TOKEN(delcopy);
      p++;
      continue;
    }

    if (!TokenStart)
      TokenStart = p;
    p++;
  }
 
  if (TokenStart)
  {
    char* tok = sdub(TokenStart, p - TokenStart);
    PUSH_TOKEN(tok);
  }

  tokens[_count] = NULL;
  *count = _count;
  return tokens;
}

lexer_t** LexStr(const char* buff, size_t* len)
{
  const char* delims = "{}[]()<>!@#$%^&*:;'-+/.,|";
  

  return (void*)0;
}

void LexFree(lexer_t **lexer, size_t len)
{
  for (size_t i = 0; i < len; ++i)
  {
    if (lexer[i]->word != NULL) free(lexer[i]->word);
    free(lexer[i]);
  }
  free(lexer);
  return;
}
