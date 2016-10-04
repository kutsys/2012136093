#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void printdir(char* dir, int depth){
        DIR* dp;
        struct dirent* entry;
        struct stat statbuf;

        if((dp = opendir(dir)) == NULL){
                fprintf(stderr,"cannot open directory: %s\n",dir);
                return;
        }

        chdir(dir);

        while((entry = readdir(dp))!=NULL){
                lstat(entry->d_name,&statbuf);
		//if(entry->d_name[0]=='.') continue;
                if(S_ISDIR(statbuf.st_mode)){//만약 디렉토리라면
                /*Found a directory, but ignore . and ..*/
                        if(entry->d_name[0]=='.')//숨김파일은 컨티뉴
				continue;
                        printf("%*s%s/\n",depth,"",entry->d_name);
                        /*Recurse at a new indent level*/
                } else {//디렉토리가 아닌 다른 파일 이라면(실행파일)
                        if(entry->d_name[0]=='.') //숨김파일은 컨티뉴
				continue;
                        printf("%*s%s\n",depth,"",entry->d_name);
		}
        }
        chdir("..");
        closedir(dp);
}

int main(){
        printf("Directory scan of /home/e:\n");
        printdir("/home/e",0);//현재 위치까지 정해주어야함(사용자 이름 e)
        printf("done.\n");
        exit(0);
}
