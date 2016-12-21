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
		sem_getvalue(sem[1], &res);
		if(res == 0){
			sem_post(sem[1]);
		}
		sem_wait(sem[0]);

		res = msgrcv(msq_id, &data, sizeof(t_data)-sizeof(long), 0, 0);
		if(res == -1){
			fprintf(stderr, "msgrcv error\n");
			return 0;
		}
		if(strcmp(data.msg.s_id,"quit")==0){
			sem_post(sem[1]);
			break;
		}

		printf("%s %d\n", data.msg.s_id, data.msg.pid);

		data.data_type = 2;
		strcpy(data.msg.name, "LSG");
		data.msg.pid = getpid();
		if(-1 == msgsnd(msq_id, &data, sizeof(t_data)-sizeof(long), 0)){
			fprintf(stderr, "msgsnd error\n");
			return 0;
		}

		sem_post(sem[1]);
		usleep(300);
	}
	sem_unlink("producer_semaphore3");
	sem_unlink("consumer_semaphore3");
}
