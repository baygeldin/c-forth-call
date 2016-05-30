#include <stdio.h>
#include "foo.h"

int foo(int a, char *b, struct bar c)
{
  printf("The integer is %d, string is \"%s\" and struct is  (%d, %d)\n", a, b, c.x, c.y);
  return 0xdeadbeef;
}
