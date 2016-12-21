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
	char buffer[10];
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
	if(temp == (void*)-1){
		fprintf(stderr, "shmat error\n");
		return 0;
	}
	sh = (shared_memory*)temp;

	while(1){
		sem_getvalue(sem[1], &res);
		if(res == 0){
			sem_post(sem[1]);
		}
		sem_wait(sem[0]);
		if(strcmp(sh->s_id,"quit")==0){
			sem_post(sem[1]);
			break;
		}

		printf("%s %d\n", sh->s_id, sh->pid);

		strcpy(sh->name,"LSG");
		sh->pid = getpid();

		sem_post(sem[1]);
		usleep(200);
	}

	if(shmdt(temp) == -1){
		fprintf(stderr,"shmdt error");
		return 0;
	}
	sem_unlink("producer_semaphore2");
	sem_unlink("consumer_semaphore2");
}
