#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/un.h>
#include<sys/socket.h>

int main(){
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char sid[11]="2012136093", pid[11], name[15], buffer[11];

	while(1){
		fgets(buffer, sizeof(buffer), stdin);

		if(strcmp(buffer,"quit\n")==0||strcmp(buffer,"q\n")==0||strcmp(buffer,"Q\n")==0){
			sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
			address.sun_family = AF_UNIX;
			strcpy(address.sun_path, "server_socket");
			len = sizeof(address);

			result = connect(sockfd, (struct sockaddr *)&address, len);
			if(result == -1){
				perror("connect error\n");
				exit(1);
			}
			strcpy(buffer, "quit");
			write(sockfd, buffer, sizeof(buffer));
			close(sockfd);
			break;
		}
		else if(strcmp(buffer, "start\n")!=0){
			continue;
		}

		sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
		address.sun_family = AF_UNIX;
		strcpy(address.sun_path, "server_socket");
		len = sizeof(address);
		
		result = connect(sockfd, (struct sockaddr *)&address, len);
		if(result == -1){
			perror("connect error\n");
			exit(1);
		}

		write(sockfd, sid, sizeof(sid));
		sprintf(pid, "%d", getpid());
		write(sockfd, pid, sizeof(pid));

		read(sockfd, name, sizeof(name));
		read(sockfd, pid, sizeof(pid));

		printf("%d, %s, %s, %s\n", getpid(), pid, sid, name);

		close(sockfd);
	}
}
