#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

#define KEY_NUM 7851

int main(){
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	char sid[11], pid[11], name[15]="LSG";

	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);

	while(1){
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		read(client_sockfd, sid, sizeof(sid));
		if(strcmp(sid,"quit")==0){
			break;
		}
		read(client_sockfd, pid, sizeof(pid));

		write(client_sockfd, name, sizeof(name));
		sprintf(pid, "%d", getpid());
		write(client_sockfd, pid, sizeof(pid));

		close(client_sockfd);
	}
}
