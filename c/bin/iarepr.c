#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // Endian converter test
  // Converts network byte order and host byte ordered and vice versa
  // Network byte order is big endian(most significant byte first) host last
  unsigned short host_port=0x1234;
  unsigned short net_port;
  unsigned long host_addr=0x12345678;
  unsigned long net_addr;

  net_port = htons(host_port); // htons host to network short order ipv4 (2bytes)
  net_addr = htonl(host_addr); // htonl host to network long order ipv6 (4bytes)

  printf("Host ordered port: %#x \n", host_port);
  printf("Network ordered port: %#x \n", net_port);
  printf("Host ordered address: %#lx \n", host_addr);
  printf("Host ordered address: %#lx \n", net_addr);
  return 0;
}
