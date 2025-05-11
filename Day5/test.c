#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char delim = '-';

int main(void){
    char string[256];
    strcpy(string,"-");
    printf("%s",strtok(string,&delim));
    printf("%s",strtok(NULL,&delim));

    return 1;
}