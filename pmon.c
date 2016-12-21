#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio_ext.h>

pid_t getPtestid(){
	FILE *p;
	int len;
	int r;
	char buf[20];

	if((p = popen("pidof ptest", "r")) == NULL){
		printf("popen error\n");
	}

	while((len = fscanf(p, "%s", buf)) > 0){
			pclose(p);
			return (pid_t)atoi(buf);
	}

	pclose(p);

	return (pid_t)-1;
}

void ptestMon(int sig){
	pid_t pid = getPtestid("ptest");
	if(pid != -1) printf("\nrunning\n>>");
	else printf("\nnot existed\n>>");

	fflush(stdout);
	alarm(5);
}

int main(){
	char ch;
	pid_t pid;

	(void) signal(SIGALRM, ptestMon);
	alarm(5);

	while(1){
		printf(">>");
		ch = getchar();
		__fpurge(stdin);

		switch(ch){
			case 'Q': case 'q':
				return 0;
				break;
			case 'K': case 'k':
				pid = getPtestid("ptest");
				if(pid != -1){
					kill(pid, SIGKILL);
				}
				break;
			case 'S': case's':
				if(getPtestid() == -1){
					system("gnome-terminal --command \"./ptest\"");
				}
				else printf("already running\n"); 
				break;
			case 'R': case 'r':
				pid = getPtestid();
				if(pid != -1){
					if(kill(pid,SIGKILL) == 0){
						system("gnome-terminal --command \"./ptest\"");
					}
				}
				else printf("ptest newly started\n");
				break;
					
			default:
				printf("command not found\n");
		}
	}

	return 0;
}
