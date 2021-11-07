#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 8080
#define SERVER_ADDRESS "0.0.0.0"
#define BUFFER_SIZE 128
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(void) {
	int fdSocket;
	struct sockaddr_in address;
  char buffer[BUFFER_SIZE];
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  memset(address.sin_zero, 0, sizeof(address.sin_zero));
    
  if ((fdSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    handle_error("socket");

  if (connect(fdSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
		close(fdSocket);
    handle_error("connect");
  }

  int n;
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("Inserte la respuesta al desafío: ");
  while ((n = read(0, buffer, BUFFER_SIZE)) > 0) {
    if (write(fdSocket, buffer, n) == -1) {
      close(fdSocket);
      handle_error("write");
    }
    printf("Inserte la respuesta al desafío: ");
  }

  if (n == -1) {
    close(fdSocket);
    handle_error("read");
  }

  close(fdSocket);

  return 0;
}
