#include <parser/lexer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <parser/split.h>

const char* delims = "{}[]()<>!@#$%^&*:;'-+/.,";

// str is expected to only 1 char long
static inline lexerIdm_t get_lexer_idm(const char* str)
{
  if (strlen(str) > 1) abort();
  switch (str[0])
  {
    case '{':
      return LexIdCurlyBracketOpen;
    case '}':
      return LexIdCurlyBracketClose;
    case '[':
      return LexIdSquareBracketOpen;
    case ']':
      return LexIdSquareBracketClose;
    case '(':
      return LexIdBracketOpen;
    case ')':
      return LexIdBracketClose;
    case '<':
      return LexIdLessThan;
    case '>':
      return LexIdGreaterThan;
    case '!':
      return LexIdExclamation;
    case '@':
      return LexIdAddSym;
    case '#':
      return LexIdHash;
    case '$':
      return LexIdDollar;
    case '%':
      return LexIdPercent;
    case '^':
      return LexIdPowHat;
    case '&':
      return LexIdAnd;
    case '*':
      return LexIdAsterisk;
    case ':':
      return LexIdColon;
    case ';':
      return LexIdSemiColon;
    case '\'':
      return LexIdQuote;
    case '-':
      return LexIdMinus;
    case '+':
      return LexIdPlus;
    case '/':
      return LexIdSlash;
    case '.':
      return LexIdDot;
    case ',':
      return LexIdComma;
    case '|':
      return LexIdPipe;
  }
  __builtin_unreachable();
}

static inline lexerId_t get_lexer_id(const char* str)
{
  if (strlen(str) == 1 && strchr(delims, str[0]))
  {
    return LexTok;
  }

  bool is_number = true;
  for (unsigned long i = 0; i < strlen(str); ++i)
  {
    switch (str[i])
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'x': // for hexadecimals
      case 'b': // for binary
        continue;
      default:
        is_number = false;
        break;
    }
  }
  if (is_number) return LexNum;
  return LexUnknownId;
}

lexer_t** LexStr(const char* buff, size_t* len)
{
  size_t TokensLen = 0;
  char** tokens = split_by_delims(buff, delims, &TokensLen);
  lexer_t** ltokens = (lexer_t**) malloc(sizeof(lexer_t*) * TokensLen);

  for (*len = 0; *len < TokensLen; *len = *len + 1)
  {
    ltokens[*len] = (lexer_t*)malloc(sizeof(lexerId_t));

    if (get_lexer_id(tokens[*len]) == LexTok)
    {
      ltokens[*len]->word = NULL;
      ltokens[*len]->id = LexTok;
      ltokens[*len]->id_exact = get_lexer_idm(tokens[*len]);
    }
    else
    {
      ltokens[*len]->id = get_lexer_id(tokens[*len]);
      // ...
    }
  }

  for (size_t i = 0; i < TokensLen; ++i) free(tokens[i]);
  free(tokens);
  return ltokens;
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
