#include <stdio.h> // for printf
#include <sys/socket.h> // for socket(), bind(), connect()
#include <arpa/inet.h> // for sockaddr_in, inet_ntoa()
#include <stdlib.h> // for atoi() and exit()
#include <string.h> // for memset()
#include <unistd.h> // for close()

int main(int argc, char *argv[]) {
  int sockfd;
  struct sockaddr_in echoServAddr;
  unsigned short echoServPort;
  char *servIP;
  char *echoString;
  char echoBuffer[32];
  unsigned int echoStringLen;
  int bytesRcvd, totalBytesRcvd;

  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
    exit(1);
  }

  servIP = argv[1];
  echoString = argv[2];

  if (argc == 4) {
    echoServPort = atoi(argv[3]);
  } else {
    echoServPort = 7;
  }

  if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("socket failed");
    exit(1);
  }

  memset(&echoServAddr, 0, sizeof echoServAddr);
  echoServAddr.sin_family = AF_INET;
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);
  echoServAddr.sin_port = htons(echoServPort);

  if (connect(sockfd, (struct sockaddr*)&echoServAddr, sizeof echoServAddr) < 0) {
    perror("connect failed");
    exit(1);
  }

  echoStringLen = strlen(echoString);
  printf("%s", echoString);

  if (send(sockfd, echoString, echoStringLen, 0) != echoStringLen) {
    perror("send set different num of bytes than expected");
    exit(1);
  }
  totalBytesRcvd = 0;
  printf("Received: \n");
  while(totalBytesRcvd < echoStringLen) {
    if ((bytesRcvd = recv(sockfd, echoBuffer, 31, 0)) == -1) {
      perror("recv failed or connection closed permanently");
      exit(EXIT_FAILURE);
    }
    totalBytesRcvd += bytesRcvd;
    echoBuffer[bytesRcvd] = '\0';
    printf("%s", echoBuffer);
  }

  printf("\n");
  close(sockfd);
  exit(0);
}
