#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>
int main(void){
    int sum = 0, string_length = 0, distance = 0,intlen1 =  0,  intlen2 = 0;
    char buffer[10000],strcopy[256] = {0}, string_int1[256] = {0}, string_int2[256] = {0}, enabled = 1;
    
    // opening file
    FILE* Fp = fopen("input.txt","r");
    
    // Makes sure file isn't corrupt
    if(Fp==NULL){
        printf("File doesn't exist");
        exit(-1);
    }
    // Reads one line from file
    while(fgets(buffer,9000,Fp)){
        string_length = strlen(buffer);
        // Searching through the string
        for(int i =  0; i<string_length; i++){
            // Checks if the string has a 'd'
            if(buffer[i] == 'd' & ((i + 6 < string_length)|(i + 3 < string_length) )){
                // Resets string
                memset(strcopy,0,256);
                strncpy(strcopy,&buffer[i],7);
                printf("%s",strcopy);
                if(!strcmp(strcopy,"don't()")){
                    enabled = 0;
                }
                strncpy(strcopy,&buffer[i],4);
                strcopy[4] = '\0';
                if(!strcmp(strcopy,"do()")){
                    enabled = 1;
                }
                printf(" Enabled is %d\n",enabled);
            }
            
            
            distance = 5;
            // Checks for the start of the multiply
            if(buffer[i] == 'm' & i+distance <= string_length & enabled){
                // Resets the both buffer strings
                memset(string_int1,0,256);
                memset(string_int2,0,256);
                // Copies and compares the mul(
                strncpy(strcopy,&buffer[i],4);
                if(strcmp(strcopy,"mul(") == 0 &  isdigit(buffer[i+4])){
                    // Now searching through the string until it is either not an integer
                    for(int j = 0;i + j + distance < string_length;j++){
                        if(!isdigit(buffer[i + distance + j])){
                            intlen1 = j;
                            break;
                        }
                    }
                    // Checks for the ,
                    if(buffer[i+distance+intlen1] == ','){
                        strncpy(string_int1,&buffer[i+distance-1],intlen1+1);
                        // Now searching through the string until it is either not an integer
                        for(int j = 0;i + distance + intlen1 + j < string_length;j++){
                            if(!isdigit(buffer[i + distance + intlen1 + j + 1])){
                                intlen2 = j;
                                break;
                            }
                        }
                        // The second integer
                        strncpy(string_int2,&buffer[i+distance+intlen1+1],intlen2);
                        // Checks for the end of the string ")"
                        if(i+distance+intlen1+intlen2+1 < string_length && buffer[i+distance+intlen1+intlen2+1] == ')'){
                            sum+= atoi(string_int1) * atoi(string_int2);
                        }
                    }
                }
            }
        }
    }
    printf("The sum is %d",sum);
}