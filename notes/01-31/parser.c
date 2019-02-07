#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SIZE 256
int pos;
char input[SIZE];

void E();
void Ep();
void T();
void Tp();
void F();

void E() {
  printf("E -> TE'\n");
  T();
  Ep();
}

void Ep() {
  printf("Ep -> +TE' | epsilon\n");
  char c = input[pos];
  printf("peek %c\n", c);
  if ('+' == c) {
    pos++;
    printf("read %c\n", c);
    T();
    Ep();
  } else {
    // epsilon
  }
}

void T() {
  printf("T -> FT'\n");
  F();
  Tp();
}

void Tp() {
  printf("T' -> *FT' | epsilon\n");
  char c = input[pos];
  printf("peek %c\n", c);
  if ('*' == c) {
    pos++; // consume the input, move to next character
    printf("read %c\n", c);
    F();
    Tp();
  } else {
    // epsilon
  }
}

void F() {
  printf("F -> 0 | 1\n");
  char c = input[pos];
  printf("peek %c\n", c);
  if ('0' == c) {
    pos++; // consume input
    printf("read %c\n", c);
  } else if ('1' == c) {
    pos++;
    printf("read %c\n", c);
  } else {
    assert(0);
  }
}

void main() {
  // starting symbol
  fscanf(stdin, "%s", input);  // overflow
  pos = 0;
  E();
  if ('$' == input[pos]) {
    printf("match $\n");
  } else {
    printf("invalid string\n");
  }
}
