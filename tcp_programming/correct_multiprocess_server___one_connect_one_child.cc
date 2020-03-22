#include "common.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

// we must catch the sigchld when forking child processed.
void SigChild(int signo);

int main() {
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	int err = 0;
	init_socket_address(serv_addr, AF_INET, nullptr, SERVER_PORT);
	err = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (err < 0) {
		::perror("bind\n");
	}
	err = listen(listenfd, 5);
	if (err < 0) {
		::perror("listen\n");
	}
	signal(SIGCHLD, SigChild);

	// we must handle interrupted system calls when catch signals.
	// accept() may be interrupted.
	for (;;) {
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		int connfd = -1;
		if ((connfd = accept(listenfd, (struct sockaddr*)&client_addr, &len)) < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				perror("accept error");
			}

			int childpid = 0;
			if ((childpid = fork()) == 0) {
				close(listenfd);
				/*
					send something to the server
				*/
				exit(0);
			}
			close(connfd);
		}
	}
}

void SigChild(int signo) {
	pid_t pid;
	int stat;

	// using loop and waitpid to prevent zombies.
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0){ 
		;;
	}
}
