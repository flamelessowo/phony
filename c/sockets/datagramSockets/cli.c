#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 1024
#define PORT 8000
void* throw_std_err(char* msg);

int main (int argc, char *argv[]) {
  int sockfd;
  char buffer[MAX_BUFFER];
  char* hi = "Hi girls";
  struct sockaddr_in cli_addr, serv_addr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("Socket creation failure");
  }
  printf("Successfully created socket %d\n", sockfd);

  memset(&cli_addr, 0, sizeof(cli_addr));
  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);

  int len, n;

  sendto(sockfd, (const char*)buffer, MAX_BUFFER, MSG_SEND, (struct sockaddr*) &serv_addr, len);
  printf("Hello sent\n");

  len = sizeof(cli_addr);

  n = recvfrom(sockfd, (char*)buffer, MAX_BUFFER, MSG_WAITALL, (struct sockaddr*)&serv_addr, &len);
  buffer[n] = '\0';
  printf("Server: %s\n", buffer);

  close(sockfd);

  exit(0);
}

void* throw_std_err(char* msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}
