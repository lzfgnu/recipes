#include "common.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>



/*
	Receiving an RST for an ESTABLISHED connection before accept is called.
	当server sleep时，client连接到server。linux server accept并没有返回error，没有复现。
*/
void server() {
	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	init_socket_address(serv_addr, AF_INET, nullptr, SERVER_PORT);


	bind(servfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(servfd, 5);
	while (true) {
		sleep(8);
		int clientfd = accept(servfd, nullptr, nullptr);
		::printf("%d\n", errno);

		if (clientfd < 0) ::printf("err\n");
		else ::printf("accepted\n");


		char buf[1024];
		int nread = read(clientfd, buf, 1024);
		::printf("nread = %d\n", nread);
		::printf("content = %s\n\n", buf);
	}

}


void client() {
	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "localhost", &serv_addr.sin_addr);
	serv_addr.sin_port = htons(9877);


	struct linger l;
	l.l_onoff = 1;
	l.l_linger = 0;
	setsockopt(servfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
	connect(servfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	char buf[] = "xxxxxx";
	write(servfd, buf, sizeof(buf));
}


int main() {
	server();
}
