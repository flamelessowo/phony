#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  
  int cm;
  while ((cm = getopt(argc, argv, "abc")) != -1) {
    switch (cm) {
      case 'a': 
        printf("a arg provided\n");
        break;
      case 'b':
        printf("b arg provided\n");
        break;
      case 'c':
        printf("c arg provided\n");
        break;
      case '?':
        printf("what the fuck did you provided?\n");
        return 1;
    }
  }

  return 0;
}
