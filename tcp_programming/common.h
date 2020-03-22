#include <sys/socket.h>

#define LISTENING_BACKLOG 1024
#define SERVER_PORT 9877
typedef struct sockaddr SA;

void init_socket_address(struct sockaddr_in& serv_addr,
												 int af_type, 
												 const char* ip_addr,
												 int port
												 );
