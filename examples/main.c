#include <stdlib.h>
#include <stdio.h>
#include <pforth.h>

typedef struct {
  int x;
  int y;
} bar;

int xyz(int a, int b);
int foo(int a, char *b, bar c);

int main() {
  pfDoForth(NULL, NULL, 0);
  return 0;
}

int foo(int a, char *b, bar c) {
  printf("The integer is %d, string is \"%s\" and struct is  (%d, %d)\n", a, b, c.x, c.y);
  return 0xdeadbeef;
}

int xyz(int a, int b) {
  printf("A is %d and B is %d", a, b);
  return (a + b);
}

