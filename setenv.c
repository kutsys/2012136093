#include<stdlib.h>
#include<stdio.h>

int main(int argc, char** argv){
    setenv(argv[1],argv[2],0);
    printf("%s = %s\n",argv[1],getenv(argv[1]));
    return 0;
}
