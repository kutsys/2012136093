#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/stat.h>

#define KEY_NUM 7851

typedef struct{
	char s_id[15];
	char name[15];
	int pid;
} msg_data;

typedef struct{
	long data_type;
	msg_data msg;
} t_data;

int main(){
	int res, my_pid, p, msq_id;
	char buffer[10], *k, sid[11]="2012136093";
	sem_t *sem[2];
	t_data data;

	my_pid = getpid();
	sem[0] = sem_open("consumer_semaphore3", O_CREAT, 0777, 0);
	sem[1] = sem_open("producer_semaphore3", O_CREAT, 0777, 0);

	msq_id - msgget((key_t)KEY_NUM, IPC_CREAT|0666);
	if(msq_id == -1){
		fprintf(stderr, "msgget error\n");
		return 0;
	}
	while(1){
		fgets(buffer, sizeof(buffer), stdin);
		if(strcmp(buffer,"quit\n")==0||strcmp(buffer,"q\n")==0||strcmp(buffer,"Q\n")==0){
			data.data_type = 2;
			strcpy(data.msg.s_id, "quit");
			printf("%s", data.msg.s_id);
			if(-1 == msgsnd(msq_id, &data, sizeof(t_data)-sizeof(long),0)){
				fprintf(stderr, "msgsnd error\n");
				return 0;
			}
			sem_post(sem[0]);
			break;
		}
		else if(strcmp(buffer, "start\n") != 0){
			continue;
		}
		sem_wait(sem[1]);
		data.data_type = 2;
		strcpy (data.msg.s_id, sid);
		data.msg.pid = my_pid;
		if(-1 == msgsnd(msq_id, &data, sizeof(t_data)-sizeof(long), 0)){
			fprintf(stderr, "msgsnd error\n");
			return 0;
		}
		sem_post(sem[0]);
		sem_wait(sem[1]);

		if(-1 == msgrcv(msq_id, &data, sizeof(t_data)-sizeof(long), 0, 0)){
			fprintf(stderr, "msgrcv error\n");
			return 0;
		}
		printf("ipc_producer: %d, %d, %s, %s\n",my_pid, data.msg.pid, data.msg.name, sid);
	}
	sem_unlink("producer_semaphore3");
	sem_unlink("consumer_semaphore3");
}

