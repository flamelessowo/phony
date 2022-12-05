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

int main(int argc, char** argv) {

}
