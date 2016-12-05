#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void main(int argc, char** argv){
	char block[1024];

	char *Oname;
	char *Cname;

	int in, out;
	int Fread;

	if(argc != 2){
		printf("복사 대상 파일만 입력 해 주세요\n");
		return;
	}
	
	Oname = argv[1];
	Cname = "CopyFile.txt";
	in = open(Oname, O_RDONLY);
	out = open(Cname, O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);

	if(in == -1){
		printf("파일이 열리지 않습니다.in\n");
		return;
	}

        if(out == -1){
                printf("파일이 열리지 않습니다.out\n");
                return;
        }

	printf("복사 시작\n");

	while((Fread = read(in , block, sizeof(block)))>0){
		sleep(1);
		printf("*");
		write(out, block, Fread);
	}

	close(in);
	close(out);
}
