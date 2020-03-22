#include "common.h"
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
void init_socket_address(struct sockaddr_in& serv_addr,
												 int af_type,
												 const char* ip_addr,
												 int port) {
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(9877);
}
