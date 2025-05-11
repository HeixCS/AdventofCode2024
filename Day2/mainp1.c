#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* delim = " ";

typedef struct linked_list{
    int data;
    struct linked_list* next;
}node;

int main(void){
    int count = 0, not_dec = 0, not_inc = 0;
    char buffer[256],*delim_str;
    FILE *Fp = fopen("input.txt","r");
    while(fgets(buffer,256,Fp)){
        not_dec = 0;
        not_inc = 0;
        node*head = (node*)malloc(sizeof(node)); 
        head->data = atoi(strtok(buffer,delim));
        
        node* current, *past;
        current = head;
        // Splitting up  the string and reading each elemnt
        delim_str = strtok(NULL,delim);
        while(delim_str != NULL){
            current->next = (node*)malloc(sizeof(node)); 
            current = current->next;
            current->next = NULL;
            current->data  = atoi(delim_str);
            delim_str = strtok(NULL,delim);
            // printf("%d ", current->data);
        }
        int past_val = head->data;
        head = head->next;
        printf("%d ", past_val);
        while(head != NULL){
            printf("%d ",head->data);
            if(abs(head->data - past_val) <= 3 && abs(head->data - past_val) >= 1){
                if(head->data > past_val){
                    not_dec = 1;
                }
                else if(head->data < past_val){
                    not_inc = 1;
                }
            }
            else {
                not_inc = 1;
                not_dec = 1;
            }
            past = head;
            past_val = past->data;
            head = head->next;
            free(past);
        }
        if((not_dec || not_inc ) & !(not_dec & not_inc)){
            count++;
            printf(" valid");
        }
        else{
            printf(" Invalid");
        }
        printf("\n");
    }
    printf("The count is %d", count);
    return 1;
}