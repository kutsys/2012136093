#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(int argc, char** argv){
	FILE* Oname;
	FILE* Cname;

	int count = 0;
	int buff_size = 102400;
	int read_value = 0;
	char * buff;

	clock_t program_start, iteration_end, program_end;

	if(argc != 2){
		printf("복사할 파일 하나만 입력 해 주세요\n");
		return;
	}


	buff = (char*)calloc(buff_size,sizeof(char));

	Oname = fopen(argv[1],"r");
	Cname = fopen("CopyHigh.txt","w");

	if(Oname == NULL || Cname == NULL){
		printf("파일이 열리지 않습니다.\n");
		return ;
	}
	printf("\n");
	program_start = clock();

	while((read_value = fread(buff,1,buff_size,Oname))>0){
		fwrite(buff,1,read_value,Cname);

		iteration_end = clock();

		if((iteration_end - program_start - count)>1){
			printf("%.3lf", (double)iteration_end - program_start - count);
			printf("*");
		}
		count = iteration_end;
	}
	program_end = clock();

	printf("\n수행시간 : [ %.3lf ]밀리초\n",(double)program_end - program_start );
	free(buff);

	fclose(Oname);
	fclose(Cname);
}
