#include<unistd.h>
#include<limits.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int test_funct(){
		static int count=0;
		struct tm *t;
		time_t timer;
		timer = time(NULL);
		t = localtime(&timer);

		count++;
		printf("%d, %d:%d:%d, %d\n", getpid(), t->tm_hour,t->tm_min,t->tm_sec,count);
		return count;
}

int main(){
		int r, res, pipe_id;
		char buf[8];

		srand(getpid());

		sprintf(&buf[2], "%d", getpid());
		buf[0] = '.';
		buf[1] = '/';

		if(access(buf, F_OK) == -1){
			res = mkfifo(buf, 0777);
			if(res != 0) exit(EXIT_FAILURE);
		}
		pipe_id = open(buf, O_WRONLY, 0777);

		while(1){
			r = rand()%10;
			res = test_funct();
			write(pipe_id, &res, sizeof(int));
			sleep(r);
		}

		close(pipe_id);

		return 0;
}
