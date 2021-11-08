#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 8080
#define SERVER_ADDRESS "0.0.0.0"
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#endif
