#include <stdio.h> // for printf
#include <sys/socket.h> // for socket(), bind(), connect()
#include <arpa/inet.h> // for sockaddr_in, inet_ntoa()
#include <stdlib.h> // for atoi() and exit()
#include <string.h> // for memset()
#include <unistd.h> // for close()
#define MAXPENDING 5

int main(int argc, char* argv[]) {
  int servsock; // socket descriptor for server
  int clientsock; // socket descriptor for client
  struct sockaddr_in serverAddr; // local address
  struct sockaddr_in clientAddr; // client address
  unsigned short servport; // server port
  unsigned int clientlen; // len of client address data struct

  if (argc != 2) { // test for correct num of args
    fprintf(stderr, "Usage: %s <server port>\n", argv[0]);
    exit(1);
  }

  servport = atoi(argv[1]); // first arg would be host port

  // Create socket for incoming connections
  if ((servsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("socket failed");
    exit(1);
  }

  // Construct local addr structure
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(servport);

  if (bind(servsock, (struct sockaddr*)&serverAddr, sizeof serverAddr) < 0) {
    perror("binding failed");
    exit(1);
  }

  if (listen(servsock, MAXPENDING) < 0) {
    perror("listen failed");
    exit(1);
  }

  for (;;) {
    clientlen = sizeof clientAddr;  

    if ((clientsock = accept(servsock, (struct sockaddr*) &clientAddr, &clientlen) < 0)) {
      perror("accept failed");
      exit(1);
    }

    printf("Handling client %s\n", inet_ntoa(clientAddr.sin_addr));
    printf("Client descriptor %d\n", clientsock);
    // Handle client
    char echoBuffer[32];
    int recvMsgSize; // size of received message
    if ((recvMsgSize = recv(clientsock, echoBuffer, 32, 0)) < 0) {
      perror("recieve failed");
      exit(1);
    }
    printf("Received: %s", echoBuffer);

    // Send received string and receive again until end of transmission
    while (recvMsgSize > 0) {
      // Echo msg back to client
      if (send(clientsock, echoBuffer, 32, 0) != recvMsgSize) {
        perror("send failed");
        exit(1);
      }
      // See if there more data to receive
      if ((recvMsgSize = recv(clientsock, echoBuffer, 32, 0)) == -1) {
        perror("recv failed");
        exit(1);
      }
    }
    close(clientsock);
  }
}
