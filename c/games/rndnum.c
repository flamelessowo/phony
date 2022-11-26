#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv) {
  srand(time(NULL));

  int rand_num = rand() % 100 + 1;

  for (;;) {
    printf("Enter num:\n"); 
    int res;
    scanf("%d", &res);
    if (res == rand_num) {
      printf("You won\n");
      break;
    } else if (res > rand_num) {
      printf("Number is lover\n");
    } else {
      printf("Number is higher\n");
    }  
  }
  return 0;
}
