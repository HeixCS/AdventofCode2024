#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
char*file_name = "input.txt"; 
const char delim = ' ';
int detect_number_of_numbers(char*string){
    int count = 1;
    for(unsigned int i = 0; i < strlen(string); i++){
        if(string[i] == ' '){
            count++;
        }
    }
    return count;
}

int main(void){
    // printf("%llu\n",ULLONG_MAX);
    int string_len = 0, result_len = 0, arr_size = 0,  not_done = 1;
    unsigned long long int sum = 0;
    unsigned long long int* array;
    unsigned long long int pos_result, result;
    char buffer[1000] = {0}, num_compy[1000], *args;
    // Opens the file
    FILE* fp = fopen(file_name,"r");
    // Reads each line
    while(fgets(buffer,1000,fp)){
        not_done = 1;
        memset(num_compy,0,256);
        result_len = 1;
        // First gets the result value
        string_len = strlen(buffer) - 1;
        if(buffer[string_len] == '\n'){
            buffer[string_len] = '\0';
        }
        else{
            string_len+=1;
        }
        
        for(int i = 1; i < string_len; i++){
            if(buffer[i] == ':'){
                break;
            }
            result_len++;
        }
        strncpy(num_compy, buffer, result_len);
        printf("%s \n", num_compy);
        // result = atoi(num_compy);
        char* endptr;
        result = strtoull(num_compy,&endptr,10);
        // Copying in the second half of the string
        strcpy(buffer,&buffer[result_len+2]);
        
        // Making the array of arguements
        arr_size = detect_number_of_numbers(buffer);
        // printf("Array size is %d\n",arr_size);
        array = (unsigned long long int*)malloc(sizeof(unsigned long long  int) * arr_size);
        args = strtok(buffer, &delim);
        array[0] = strtoull(args,&endptr,10);
        printf("%d ", array[0]);
        for(int i = 1; i < arr_size; i++){
            args = strtok(NULL, &delim);
            array[i] = strtoull(args,&endptr,10);
            printf("%llu ", array[i]);
        }
        printf("\n");
        // Creating initial operation order
        char* opp_order = (char*)malloc(sizeof(char) * (arr_size));
        for(int i = 0; i < arr_size-1; i++){
            opp_order[i] = '+';
        }
        opp_order[arr_size - 1] = '\0';

        // Now considering each possible operation
        while(not_done){
            not_done = 0;
            // Initial sum
            if(opp_order[0] == '*'){
                pos_result = array[0] * array[1];
            }
            else{
                pos_result = array[0] + array[1];
            }
            // Calculating  the rest of the sum
            for(int i = 1; i < arr_size - 1; i++){
                if(opp_order[i] == '*'){
                    pos_result = pos_result * array[i+1];
                }
                else{
                    pos_result = pos_result + array[i+1];
                }
            }

            // Checks if the value is valid
            if(pos_result == result){
                sum = sum + pos_result;
                break;
            }

            // Updates the opperation order
            for(int i = 0; i  < arr_size - 1; i++){
                if(opp_order[i] == '+'){
                    opp_order[i] = '*';
                    for(int j = i - 1; j >= 0;j--){
                        opp_order[j] = '+';
                    }
                    not_done = 1;
                    break;
                }
            }
        }
        free(opp_order);
        free(array);
    }
    printf("The result is %llu\n", sum);
}


