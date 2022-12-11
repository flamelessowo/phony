#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXPENDING 10

typedef struct sockaddr_in tcpipv4;

void throw_std_err(char* message) {
  perror(message);
  exit(EXIT_FAILURE);
}

void fill_addr_structure(tcpipv4* addr, char* ip, int port) {
  memset(*&addr, 0, sizeof(*addr)); 
  addr->sin_family = AF_INET;
  inet_pton(AF_INET, ip, &addr->sin_addr);
  addr->sin_port = htons(port);
}

int create_socket_wrap(int domain, int type, int protocol) {
  int sock;
  if ((sock = socket(domain, type, protocol)) == -1) {
    throw_std_err("descriptor cration failure"); 
  }
  printf("Successfully created socket %d\n", sock);
  return sock;
}

void bind_socket_wrap(int sock, tcpipv4 *addr) {
  if (bind(sock, (struct sockaddr*)*&addr, sizeof(*addr)) == -1) {
    throw_std_err("bind failure");
  }
  printf("Successfully binded socket\n");
}

void start_listen_wrap(int sock, int backlog) {
  if (listen(sock, backlog) == -1) {
    throw_std_err("listen failure");
  }
  printf("Successfully listening up to %d clients\n", backlog);
}

int accept_wrap(int sock, tcpipv4* client_adr, int client_len) {
  int client_socket;
  if ((client_socket = accept(sock, (struct sockaddr*)*&client_adr, &client_len)) == -1) {
    throw_std_err("accept failure");
  }
  printf("Successfully accept from %d\n", client_socket); 
  return client_socket;
}

int main(int argc, char** argv) {
  int servsock, clientsock;
  struct sockaddr_in serv_addr, client_addr;
  int serv_port;
  int client_len;
  char buffer[1024];
  
  //getopt part
  int optChar;
  char* ip = "127.0.0.1";
  char* port = "8000";
  while ((optChar = getopt(argc, argv, "p:a:")) != -1) {
    switch(optChar) {
      case 'p':
        port = optarg;  
        break;
      case 'a':
        ip = optarg;
        break;
    }
  } 
  if (ip == NULL || port == NULL) {
    printf("correct ip and port must be provided\n"); 
    return 1;
  }

  serv_port = atoi(port);

  servsock = create_socket_wrap(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  fill_addr_structure(&serv_addr, ip, serv_port);
  bind_socket_wrap(servsock, &serv_addr);
  start_listen_wrap(servsock, MAXPENDING);

  for (;;) {
    client_len = sizeof(client_addr);
    printf("Waiting for clients...\n");
    clientsock = accept_wrap(servsock, &client_addr, client_len); 
    char *client_ip = inet_ntoa(client_addr.sin_addr);
    printf("Accepted new connection from a client %s:%d\n", client_ip, ntohs(client_addr.sin_port)); 
    memset(buffer, 0, sizeof(buffer));
    int size = read(clientsock, buffer, sizeof(buffer));
    if (size < 0) {
      throw_std_err("Read error");
    }
    printf("Received %s from client\n", buffer);
    if (write(clientsock, buffer, size) < 0) {
      throw_std_err("Write error");
    }
    close(clientsock);
  }
  close(servsock); 
  exit(0);
}
