#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct sockaddr_in tcpipv4;

void throw_std_err(char* message) {
  perror(message);
  exit(EXIT_FAILURE);
}

int create_socket_wrap(int domain, int type, int protocol) {
  int sock;
  if ((sock = socket(domain, type, protocol)) == -1) {
    throw_std_err("descriptor cration failure"); 
  }
  printf("Successfully created socket %d\n", sock);
  return sock;
}

void connect_wrap(int socket, tcpipv4* address, int address_len) {
  if (connect(socket, (struct sockaddr*)*&address, address_len) < 0) {
    throw_std_err("connect to server failure\n");
  }
  printf("Successfully connected to server %d\n", socket);
}

void fill_addr_structure(tcpipv4* addr, char* ip, int port) {
  memset(*&addr, 0, sizeof(*addr)); 
  addr->sin_family = AF_INET;
  inet_pton(AF_INET, ip, &addr->sin_addr);
  addr->sin_port = htons(port);
}

int main(int argc, char** argv) {

  int serverfd;
  tcpipv4 server;
  int len;
  int port = 8000;
  char* server_ip = "127.0.0.1";
  char* buffer = "hello server";
  if (argc == 3) {
    server_ip = argv[1];
    port = atoi(argv[2]);
  }
  serverfd = create_socket_wrap(AF_INET, SOCK_STREAM, 0);
  fill_addr_structure(&server, server_ip, port);
  len = sizeof(server);
  connect_wrap(serverfd, &server, len);
  if (write(serverfd, buffer, strlen(buffer)) < 0) {
    throw_std_err("write error");
  }
  char recv[1024];
  memset(recv, 0, sizeof(recv));
  if (read(serverfd, recv, sizeof(recv)) < 0) {
    throw_std_err("read error");
  }
  printf("Received %s from server\n", recv);
  close(serverfd);
  exit(0);
}
