#include <stdio.h>

int main() {
  printf("STARTED RUNNING\n");
  
  double temp = (double)2;
  int y = 1.7 * temp;
  /* int y = ((void *)1.7) * (float)((void *)2); */
  
  float yf = 1.7 * 2;

  printf("%x\n", y);
  printf("%f\n", yf);

  

  return 0;
}
