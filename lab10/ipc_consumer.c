#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	pid_t pid;
	int res, pipe_id[2], p, my_pid;
	char buffer[10], value[30], *pipe_name[2]={"./pipe1", "./pipe2"};

	if(access(pipe_name[0], F_OK) == -1){
		res = mkfifo(pipe_name[0], 0777);
		if(res!=0) exit(EXIT_FAILURE);
	}
	if(access(pipe_name[1], F_OK) == -1){
		res = mkfifo(pipe_name[1], 0777);
		if(res!=0) exit(EXIT_FAILURE);
	}

	pipe_id[1] = open(pipe_name[1], O_WRONLY, 0777);
	pipe_id[0] = open(pipe_name[0], O_RDONLY, 0777);
	
	while(1){
		memset(value, 0, sizeof(value));
		read(pipe_id[0], value, sizeof(value));
		if(strcmp(value,"quit\n")==0||strcmp(value,"q\n")==0||strcmp(value,"Q\n")==0) break;
		if(strcmp(value, "\0") != 0) continue;
		printf("ipc_consumer: %s\n", value);
		memset(value, 0, sizeof(value));
		sprintf(value, "%s %d ", "LSG", getpid());
		write(pipe_id[1], value, sizeof(value));
	}
	close(pipe_id[0]);
	close(pipe_id[1]);
	unlink(pipe_name[0]);
	unlink(pipe_name[1]);
}

