#pragma once
#include <stdlib.h>

enum LexerId {
  UnknownId,
};
typedef enum LexerId lexerId_t;

struct Lexer {
  char* word;
  lexerId_t id;
};
typedef struct Lexer lexer_t;

lexer_t** LexStr(const char* buff, size_t* len);
void LexFree(lexer_t** lexer, size_t len);
