#include "./include/connection.h"
#include "./include/game.h"

#define MAX_PENDING_CONNECTIONS 1

int main(void) {
  int fdSocket;
	struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  memset(address.sin_zero, 0, sizeof(address.sin_zero));
    
  if ((fdSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_IP)) == -1)
    handle_error("socket");

  int option = 1;
  if (setsockopt(fdSocket, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option)) == -1) {
    close(fdSocket);
    handle_error("setsockopt"); 
  }

  if (bind(fdSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
		close(fdSocket);
    handle_error("bind");
  }
  
  if (listen(fdSocket, MAX_PENDING_CONNECTIONS) == -1){
    close(fdSocket);
    handle_error("Error in listen");
  }
  
  int fdClient, addrlen = sizeof(address);
  if ((fdClient = accept(fdSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) == -1) {
    close(fdSocket);
    handle_error("accept");
  }

  setvbuf(stdout, NULL, _IONBF, 0);

  gameLoop(fdClient);

  close(fdClient);
  close(fdSocket);

  return 0;

}