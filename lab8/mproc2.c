#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pthread.h>

#define NUM_OF_THREAD 10

void* subproc(void *arg){
	int *count= (int *)arg;
	struct tm *t;
	time_t timer;

	while(1){
		sleep(rand()%10);

		timer = time(NULL);
		t = localtime(&timer);

		(*count)++;
		printf("%lu, %d:%d:%d, %d\n", pthread_self(), t->tm_hour, t->tm_min, t->tm_sec, *count);
		fflush(stdout);
	}
	return NULL;
}

int isThread(){
	FILE *p;
	int count=0, len;
	char *re;
	char buf[3][15];

	if((p = popen("ps -aL", "r")) == NULL){
		printf("popen error\n");
	}

	while((len = fscanf(p, "%s %s %*s %*s", buf[0], buf[1])) > 0 && (re = fgets(buf[2], 15, p)) != NULL){
		if((strcmp(buf[2], " mproc2\n") == 0) && (strcmp(buf[0], buf[1]) != 0)){
			count++;
		}
	}

	pclose(p);
	return count;
}

int main(){
	int res, j, i;
	pthread_t tid[NUM_OF_THREAD];
	int count[NUM_OF_THREAD] = {0};

	srand(time(NULL));

	printf("2012136093 LSG\n");

	for(i=0;i<NUM_OF_THREAD;i++){
		res = pthread_create(&tid[i], NULL, subproc, &count[i]);
		pthread_detach(tid[i]);
			if(res != 0){
				perror("Thread is not created");
				exit(EXIT_FAILURE);
			}
		}
		i=0;
		while(isThread()){
			usleep(200);
			for(j=0;j<NUM_OF_THREAD;j++){
				if(tid[j] == -1) continue;
				if(count[j] >= 20){
					i++;
					pthread_cancel(tid[j]);
					printf("%d : %lu terminated\n", i, tid[j]);
					tid[j] = -1;
				}
			}
		}
		printf("finished thread\n");
		return 0;
}
