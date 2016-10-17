#include<stdlib.h>
#include<stdio.h>

int main(int argc, char** argv){
    char* value;
    value = getenv(argv[1]);
    if(value!=NULL){
        printf("%s = %s \n",argv[1], value);
    }
    return 0;
} 
