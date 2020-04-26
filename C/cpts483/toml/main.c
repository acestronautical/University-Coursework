#include "chan/chan.h"
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct _String {
  char *ptr;
  unsigned int len;
};
typedef struct _String String;

typedef chan_t Channel;

struct _Lexer {
  Channel *emitter;
  String input;
  unsigned int line;
  unsigned int pos;
  unsigned int start;
};
typedef struct _Lexer Lexer;

struct _StateFn {
  struct _StateFn (*ptr)(Lexer *lx);
};
typedef struct _StateFn StateFn;

Lexer *lx_create(FILE *f) {
  Lexer *lx = (Lexer *)malloc(sizeof(Lexer));
  // allocate channel
  lx->emitter = chan_init(10);
  // read input string
  fseek(f, 0, SEEK_END);
  lx->input.len = ftell(f);
  fseek(f, 0, SEEK_SET);
  lx->input.ptr = (char *)malloc(lx->input.len);
  fread(lx->input.ptr, 1, lx->input.len, f);
  fclose(f);
  // other fields
  lx->line = 1;
  lx->pos = 0;
  lx->start = 0;
  return lx;
}

enum _TokenType {
  l_par = '(',
  r_par = ')',
  l_sqr = '[',
  r_sqr = ']',
  l_crl = '{',
  r_crl = '}',
};
typedef enum _TokenType TokenType;

struct _Token {
  TokenType ID;
  unsigned int line;
  String val;
};
typedef struct _Token Token;

Token tkn_create(Lexer *lx, int ID) {
  return (Token){
      l_par, lx->line, {lx->input.ptr + lx->pos, lx->pos - lx->start}};
}

char lx_next(Lexer *lx) {
  if (lx->pos >= lx->input.len) {
    return EOF;
  } else {
    char c = lx->input.ptr[lx->pos++];
    if (c == '\n') {
      lx->line++;
    }
    return c;
  }
}

void *lx_backup(Lexer *lx) { lx->pos -= 1; }

void *lx_ignore(Lexer *lx) { lx->start = lx->pos; }

void *lx_emit(Lexer *lx, Token *tkn) {
  chan_send(lx->emitter, (void *)tkn);
  // printf("Sent: Token{.ID=%d, .line=%d}\n", t->ID, t->line);
}

StateFn lexBegin(Lexer *lx) {
  char c;
  Token tkn;
  while ((c = lx_next(lx)) != EOF) {
    if (isspace(c)) {
      lx_ignore(lx);
    } else if (c == l_par) {
      tkn = tkn_create(lx, l_par);
      lx_emit(lx, &tkn);
    } else if (c == r_par) {
      tkn = tkn_create(lx, r_par);
      lx_emit(lx, &tkn);
    } else if (c == l_sqr) {
      tkn = tkn_create(lx, l_sqr);
      lx_emit(lx, &tkn);
    } else if (c == r_sqr) {
      tkn = tkn_create(lx, r_sqr);
      lx_emit(lx, &tkn);
    }
  }
  chan_close(lx->emitter);
  return (StateFn){NULL};
}

void *lx_run(Lexer *lx) {
  for (StateFn sf = (StateFn){lexBegin}; sf.ptr;) {
    sf = sf.ptr(lx);
  }
}

int main(int argc, char const *argv[]) {
  FILE *f = fopen(argv[1], "r");
  Lexer *lexer = lx_create(f);
  pthread_t th;
  pthread_create(&th, NULL, (void *)lx_run, lexer);

  void *msg;
  Token *tkn;
  while (chan_recv(lexer->emitter, &msg) == 0) {
    tkn = (Token *)msg;
    printf("Recieved: Token{.ID=%d, .line=%d}\n", tkn->ID, tkn->line);
  }
}
