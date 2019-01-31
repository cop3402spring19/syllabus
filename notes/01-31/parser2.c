#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SIZE 256
char pos;
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
  char c = input[++pos];
  printf("read %c\n", c);
  if ('+' == c) {
    printf("match %c\n", c);
    T();
    Ep();
  } else {
    // epsilon
    printf("unread %c\n", c);
    pos--;
  }
}

void T() {
  printf("T -> FT'\n");
  F();
  Tp();
}

void Tp() {
  printf("Tp -> *FT' | epsilon\n");
  char c = input[++pos];
  printf("read %c\n", c);
  if ('*' == c) {
    printf("match %c\n", c);
    F();
    Tp();
  } else {
    // epsilon
    printf("unread %c\n", c);
    pos--;
  }
}

void F() {
  printf("F -> 0 | 1\n");
  char c = input[++pos];
  printf("read %c\n", c);
  if ('0' == c) {
    printf("match %c\n", c);
  } else if ('1' == c) {
    printf("match %c\n", c);
  } else {
    printf("invalid factor\n");
    exit(1);
  }
}

void main() {
  // starting symbol
  fscanf(stdin, "%s", input);  // overflow
  pos = -1;
  E();
  char c = input[++pos];
  printf("read %c\n", c);
  if ('$' == input[pos]) {
    printf("match $\n");
  } else {
    printf("invalid string\n");
  }
}
