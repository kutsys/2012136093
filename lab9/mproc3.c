#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pthread.h>

#define NUM_OF_THREAD 10

sem_t my_sem;
int min_count=0, res=0;
int count[NUM_OF_THREAD]={0};
pthread_t tid[NUM_OF_THREAD];

int getMinCount(){
	int min=count[0], i;
	for(i=0;i<NUM_OF_THREAD;i++){
		if(count[i]<min) min = count[i];
	}
	return min;
}

void* subproc(void *arg){
	int k= *(int *)arg;
	int j, num=0;
	struct tm *t;
	time_t timer;

	while(1){
		sem_wait(&my_sem);

		min_count = getMinCount();
		if(count[k] <= min_count){
			timer = time(NULL);
			t = localtime(&timer);

			count[k]++;
			printf("%lu, %d:%d:%d, %d\n", pthread_self(), t->tm_hour, t->tm_min, t->tm_sec, count[k]);
			fflush(stdout);
			sem_post(&my_sem);
			sleep(rand()%10);
		}
		else{
			sem_post(&my_sem);
		}
		if(count[k] == 20) break;
	}
	return NULL;
}

int isThread(){
	FILE *p;
	int count=0, len;
	char *re;
	char buf[3][15];

	if((p = popen("ps -al", "r")) == NULL){
		printf("popen error\n");
	}
	while((len = fscanf(p, "%s %s %*s %*s", buf[0], buf[1])) > 0 && (re = fgets(buf[2], 15, p)) != NULL){
		if((strcmp(buf[2], "mproc3\n") == 0) && (strcmp(buf[0], buf[1]) != 0)){
			count++;
		}
	}
	pclose(p);
	return count;
}

int main(){
	int res, j, i;
	void *result;

	sem_init(&my_sem, 0, 0);
	srand(time(NULL));

	printf("2012136093 LSG\n");

	for(i=0;i<NUM_OF_THREAD;i++){
		res = pthread_create(&tid[i], NULL, subproc, (void *)&i);
		if(res !=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
		sleep(1);
	}
	i = 0;
	sem_post(&my_sem);
	for(j=0;j<NUM_OF_THREAD;j++){
		res = pthread_join(tid[j], &result);
		if(res != 0) perror("join error");
	}
	printf("finished thread\n");
	sem_destroy(&my_sem);
	return 0;
}
