#pragma once
#include <stdlib.h>

enum LexerId {
  LexUnknownId,
  LexTok,
  LexNum,
};
typedef enum LexerId lexerId_t;

enum LexerIdM {
  LexIdCurlyBracketOpen,
  LexIdCurlyBracketClose,
  LexIdSquareBracketOpen,
  LexIdSquareBracketClose,
  LexIdBracketOpen,
  LexIdBracketClose,
  LexIdLessThan,
  LexIdGreaterThan,
  LexIdExclamation,
  LexIdAddSym,
  LexIdHash,
  LexIdDollar,
  LexIdPercent,
  LexIdPowHat,
  LexIdAnd,
  LexIdAsterisk,
  LexIdColon,
  LexIdSemiColon,
  LexIdQuote,
  LexIdMinus,
  LexIdPlus,
  LexIdSlash,
  LexIdDot,
  LexIdComma,
  LexIdPipe,
};
typedef enum LexerIdM lexerIdm_t;

struct Lexer {
  char* word;
  lexerId_t id;
  lexerIdm_t id_exact;
};
typedef struct Lexer lexer_t;

lexer_t** LexStr(const char* buff, size_t* len);
void LexFree(lexer_t** lexer, size_t len);
