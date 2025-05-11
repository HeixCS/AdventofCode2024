#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct file_info{
    int line_count;
    int line_size;
}file_in;


void find_line_count(char*file_name, file_in* info){
    //Opens the file
    FILE* fp = fopen("input.txt","r");
    char buffer[1000];

    // Finding length of the buffer
    fgets(buffer,1000,fp);
    info->line_size = strlen(buffer) - 1;
    
    // Reading the whole file
    int line_count = 1;
    while(fgets(buffer,1000,fp)){
        line_count++;
    }
    // Setting value
    info->line_count = line_count;

    fclose(fp);
    return;
}
char*file_name = "input.txt";

int main(void){
    char buffer[1000] = {0};
    int string_len = 0, count = 0;

    // Getting info about the file
    file_in input;
    input.line_count = 0;
    find_line_count(file_name,&input);
    printf("The line count is %d and line size is %d\n", input.line_count,input.line_size);
    
    //Opens the file an makes sure it exists
    FILE* fp = fopen(file_name,"r");
    
    // Making array to hold file
    char**array = (char**)malloc(input.line_count * sizeof(char*));
    for(int i = 0 ; i < input.line_count;i++){
        array[i] = (char*)malloc(input.line_size + 1);
    }
    // Reading the whole file
    for(int i = 0; i < input.line_count;i++){
        fgets(buffer,input.line_size+2,fp);
        strcpy(array[i],buffer);
        array[i][input.line_size] = '\0';
        // printf("%s\n", array[i]);
    }

    for(int i = 0; i < input.line_count; i++){
        for(int j = 0; j < input.line_size;j++){
            if(array[i][j] == 'X'){
                printf("i: %d j: %d ",i,j);
                // Checking the right
                if(j + 3 < input.line_size){
                    strncpy(buffer,&array[i][j],4);
                    buffer[4] = '\0';
                    printf("%s",buffer);
                    if(!strcmp(buffer,"XMAS")){
                        count++;
                    }
                }
                // Checking the left
                if(j - 3 >= 0){
                    strncpy(buffer,&array[i][j - 3],4);
                    buffer[4] = '\0';
                    printf(" %s",buffer);
                    if(!strcmp(buffer,"SAMX")){
                        count++;
                    }
                }
                // Checking down
                if(i + 3 < input.line_count){
                    for(int k = 0; k < 4;k++){
                        buffer[k] = array[i+k][j];
                    }
                    buffer[4] = '\0';
                    printf(" %s",buffer);
                    if(!strcmp(buffer,"XMAS")){
                        count++;
                    }
                }
                // Checking Up
                if(i - 3 >= 0){
                    for(int k = 0; k < 4;k++){
                        buffer[k] = array[i-k][j];
                    }
                    buffer[4] = '\0';
                    printf(" %s",buffer);
                    if(!strcmp(buffer,"XMAS")){
                        count++;
                    }
                }
                // Checking upper diagonal
                if(i - 3 >= 0){
                    if(j + 3 < input.line_size){
                        for(int k = 0; k < 4;k++){
                            buffer[k] = array[i-k][j+k];
                        }
                        buffer[4] = '\0';
                        printf(" %s",buffer);
                        if(!strcmp(buffer,"XMAS")){
                            count++;
                        }
                    }
                }
                // Checking upper left diagonal
                if(i - 3 >= 0){
                    if(j - 3 >= 0){
                        for(int k = 0; k < 4;k++){
                            buffer[k] = array[i-k][j-k];
                        }
                        buffer[4] = '\0';
                        printf(" %s",buffer);
                        if(!strcmp(buffer,"XMAS")){
                            count++;
                        }
                    }
                }
                // Checking down right diagonal
                if(i + 3 < input.line_count){
                    if(j + 3 < input.line_size){
                        for(int k = 0; k < 4;k++){
                            buffer[k] = array[i+k][j+k];
                        }
                        buffer[4] = '\0';
                        printf(" %s",buffer);
                        if(!strcmp(buffer,"XMAS")){
                            count++;
                        }
                    }
                }
                // Checking down left diagonal
                if(i + 3 < input.line_count){
                    if(j - 3 >= 0){
                        for(int k = 0; k < 4;k++){
                            buffer[k] = array[i+k][j-k];
                        }
                        buffer[4] = '\0';
                        printf(" %s",buffer);
                        if(!strcmp(buffer,"XMAS")){
                            count++;
                        }
                    }
                }
                printf("\n");
            }
        }
    }
    printf("Count is %d", count);
    // Freeing the whole array
    for(int i = 0 ; i < input.line_count;i++){
        free(array[i]);
    }
    free(array);
    fclose(fp);
    return 1;
}