#include <stdio.h>

int main() {
  printf("STARTED RUNNING\n");
  
  float x = 1.7;

  float *p = &x;
  int *ip = (int *)p;
  
  printf("%d\n", *ip);  
  
  return 0;
}
