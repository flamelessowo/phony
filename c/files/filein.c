#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFSIZE 120

int main(int argc, char* argv[]) {
  int fd, opt;
  int aflag;
  while ((opt = getopt(argc, argv, "af:w:")) != -1) {
    switch (opt) {
      case 'a':
        printf("amode on\n");
        aflag = 1;
        break;
      case 'f':
        if (aflag) {
          
        } else {

        }
        if ((fd = open(optarg, O_RDWR)) == -1) {
          perror("Error while opening file\n");
          exit(EXIT_FAILURE);
        }
        printf("descriptor on\n");
        break;
      case 'w':
        if (sizeof optarg > BUFFSIZE) {
          printf("string exceeds buffer\n");
          exit(1);
        } else {
          // pass
        }
      case '?':
        printf("why so bad???\n");
    } 
  }

  int bytesWritten = write(fd, "hello world", 11);
  if (bytesWritten == -1) {
    perror("problem with write");
    exit(EXIT_FAILURE);
  }
  printf("Written %d\n", bytesWritten);
  close(fd);
  return 0;
}
