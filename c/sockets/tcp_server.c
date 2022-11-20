#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#define PORT 8080

int main(int argc, char *argv[]) {
  int server_fd, newsock_fd; // file descriptor for server 
  struct sockaddr_in address = {0}; // structure that contains TCP information of current (server)
  char* hello = "hi there";
  char buff[1024] = {0};
  
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // check if TCP socket created. If no throw error
    perror("socket failed");
    exit(EXIT_FAILURE); 
  }

  address.sin_family = AF_INET; // define family for socket address. Current IPv4
  // port value on host an network can have different byde order!
  address.sin_port = htons(PORT); // htons(host to network short val) converts from host byte order to network byte order

  if (bind(server_fd, (struct sockaddr*)&address, sizeof address) == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 5) == -1) {
    perror("listen failed");  
    exit(EXIT_FAILURE);
  }
  socklen_t adrlen = sizeof address;
  if ((newsock_fd = accept(server_fd, (struct sockaddr*)&address, &adrlen)) == -1) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  read(newsock_fd, buff, 1024);
  printf("%s\n", buff);
  send(newsock_fd, hello, strlen(hello), 0);
  printf("Hello message sent");

  close(newsock_fd);

  shutdown(server_fd, SHUT_RDWR);

  printf("%d", server_fd);
  return 0;
}
