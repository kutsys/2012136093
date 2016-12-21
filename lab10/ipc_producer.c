#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

char* replaceChar(char *str, const char a, const char b, const int len){
	int i;
	char *re = NULL;

	for(i=0;str[i] != '\0' && i < len; i++){
		if(str[i] == a){
			str[i] = b;
			re = &str[i+1];
			break;
		}
	}
	return re;
}

int main(){
	pid_t pid;
	int res, pipe_id[2], p, my_pid;
	char buffer[10], *k, value[30], sid[11]="2012136093", *pipe_name[2]={"./pipe1", "./pipe2"};

	if(access(pipe_name[0], F_OK) == -1){
		res = mkfifo(pipe_name[0], 0777);
		if(res!=0) exit(EXIT_FAILURE);
	}
	if(access(pipe_name[1], F_OK) == -1){
		res = mkfifo(pipe_name[1], 0777);
		if(res!=0) exit(EXIT_FAILURE);
	}

	pipe_id[1] = open(pipe_name[1], O_RDONLY, 0777);
	pipe_id[0] = open(pipe_name[0], O_WRONLY, 0777);
	
	my_pid = getpid();
	
	while(1){
		memset(value, 0, sizeof(value));
		sprintf(value, "%s %d ", sid, my_pid);
		fgets(buffer, sizeof(buffer), stdin);

		if(strcmp(buffer,"quit\n")==0||strcmp(buffer,"q\n")==0||strcmp(buffer,"Q\n")==0){
			write(pipe_id[0], buffer, sizeof(buffer));
			break;
		}
		else if(strcmp(buffer, "start\n") != 0){
			printf("%s", buffer);
			continue;
		}
		write(pipe_id[0], value, sizeof(value));

		memset(value, 0, sizeof(value));
		read(pipe_id[1], value, sizeof(value));

		k = replaceChar(value, ' ', '\0', sizeof(value)/sizeof(char));

		printf("ipc_producer: %d, %s, %s, %s\n", my_pid, k, value, sid);
	}
	close(pipe_id[0]);
	close(pipe_id[1]);
	unlink(pipe_name[0]);
	unlink(pipe_name[1]);
}

