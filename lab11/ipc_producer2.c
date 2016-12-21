#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>

#define KEY_NUM 7851

typedef struct{
	char s_id[15];
	char name[15];
	int pid;
} shared_memory;

int main(){
	int res, my_pid, p, shmem_id;
	char buffer[10], *k, sid[11]="2012136093";
	sem_t *sem[2];
	shared_memory *sh;
	void *temp;

	my_pid = getpid();
	sem[0] = sem_open("consumer_semaphore2", O_CREAT, 0777, 0);
	sem[1] = sem_open("producer_semaphore2", O_CREAT, 0777, 0);

	shmem_id = shmget((key_t)KEY_NUM, sizeof(shared_memory), 0666|IPC_CREAT);
	if(shmem_id == -1){
		fprintf(stderr, "shmget error\n");
		return 0;
	}
	temp = shmat(shmem_id, (void *)0, 0);
	if(temp == (void *)-1){
		fprintf(stderr, "shmat error\n");
		return 0;
	}
	sh = (shared_memory*)temp;
	while(1){
		fgets(buffer, sizeof(buffer), stdin);
		if(strcmp(buffer,"quit\n")==0||strcmp(buffer,"q\n")==0||strcmp(buffer,"Q\n")==0){
			strcpy(sh->s_id, "quit");
			printf("%s", sh->s_id);
			sem_post(sem[0]);
			break;
		}
		else if(strcmp(buffer, "start\n") != 0){
			continue;
		}
		sem_wait(sem[1]);
		strcpy(sh->s_id, sid);
		sh->pid = my_pid;

		sem_post(sem[0]);
		sem_wait(sem[1]);
		printf("ipc_producer: %d, %d, %s, %s\n", my_pid, sh->pid, sh->name, sh->s_id);
	}

	if(shmdt(temp) == -1){
		fprintf(stderr, "shmdt error");
		return 0;
	}
	sem_unlink("producer_semaphore2");
	sem_unlink("consumer_semaphore2");
}
