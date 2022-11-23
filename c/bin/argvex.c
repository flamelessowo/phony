#include<stdio.h>

int main(int argc, char* argv[]) {
  
  printf("Argc: %d\n", argc);
  printf("Argv: %s\n", argv[1]);
  argc < 2 ? printf("Argv: %s\n", argv[2]) : printf("Dead\n");
  return 0;
}
