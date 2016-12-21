#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

void alarmFunc(int sig){
	struct tm *ntime;
	time_t _time;
	_time = time((time_t *)0);
	ntime = localtime(&_time);

	printf("%d.%d.%.d %d:%d:%d\n",ntime->tm_year+1900, ntime->tm_mon+1, ntime->tm_mday, ntime->tm_hour, ntime->tm_min, ntime->tm_sec);

	alarm(2);
}

int main(){
	(void) signal(SIGALRM, alarmFunc);

	alarm(2);

	while(1){
		sleep(5);
	}

	return 0;
}
