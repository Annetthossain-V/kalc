#pragma once
#include <stdbool.h>
#include <parser/lexer.h>

enum p_op {
  PsrPlus,
  PsrPlusEqual,
};
typedef enum p_op p_op;

struct Expr {
  char** ident;
  p_op** op;
  unsigned int ident_len;
  unsigned int op_len;
};
typedef struct Expr Expr;

struct ParserP {
  bool is_expr;
  Expr* expr;
  lexer_key_word_t lkw;
  char** word; // invalid if expr; always one after lkw
  unsigned int word_len;
};
typedef struct ParserP ParserP;

static inline void FreeParserPP(ParserP** parser, size_t ParserLen)
{
  for (size_t i = 0; i < ParserLen; ++i)
  {

  }
}

// main parser
ParserP** ParseLexerToCodegenBcode(size_t* ParserLen, lexer_t** lexer_code, size_t lexer_len);
