#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "8000"
#define MAX_BUFFER 1024

void* throw_error(int exit_status, char* msg);
void* throw_std_error(char* msg);

int main (int argc, char *argv[]) {
  int serv_des;
  int serv_port;
  struct sockaddr_in serv_addr, cli_addr;
  char* serv_ip;
  char buffer[MAX_BUFFER];

  if (argc >= 3) {
    serv_ip = argv[2];
    serv_port = atoi(argv[3]);
  } else {
    serv_ip = DEFAULT_IP;
    serv_port = atoi(DEFAULT_PORT);
  }

  if ((serv_des = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    throw_std_error("Error creating socket");
  }
  printf("Successfully created socket %d\n", serv_des);

  memset(&serv_addr, 0, sizeof(serv_addr)); 
  memset(&cli_addr, 0, sizeof(cli_addr)); 

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(serv_port);

  if (bind(serv_des, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
    throw_std_error("Error binding socket"); 
  }
  printf("Successfully binded socket %d\n", serv_des);

  for(;;) {

    int len, n;
    len = sizeof(cli_addr);

    n = recvfrom(serv_des, (char*)buffer, MAX_BUFFER, MSG_WAITALL, (struct sockaddr*) &cli_addr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(serv_des, (const char*)"hello", strlen("hello"), MSG_SEND, (struct sockaddr*) &cli_addr, len);
    printf("Hello sent\n");
  }

  exit(0);
}

void* throw_std_error(char* msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}
