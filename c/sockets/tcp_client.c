#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
  int sockfd;
  struct sockaddr_in serv_addr;
  char* hello = "Hello from client";
  char buffer[1024] = {0};
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0) {
    perror("bad ip provided");
    exit(EXIT_FAILURE);
  }

  int clientfd;
  if ((clientfd = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof serv_addr)) < 0) {
    perror("connection failed");
    exit(EXIT_FAILURE);
  }
  send(sockfd, hello, strlen(hello), 0);
  printf("Hello sent\n");
  read(sockfd, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
}
