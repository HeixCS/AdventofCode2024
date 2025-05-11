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
    int count = 0, not_dec = 0, not_inc = 0, num_item=0, current_itt = 0, valid = 0;
    char buffer[256],*delim_str;
    node*root;
    FILE *Fp = fopen("input.txt","r");
    while(fgets(buffer,256,Fp)){
        // Default values
        num_item = 1;
        not_dec = 0;
        not_inc = 0;
        node*head = (node*)malloc(sizeof(node)); 
        
        // Splitting up a string
        head->data = atoi(strtok(buffer,delim));
        node* current, *past;
        current = head;
        delim_str = strtok(NULL,delim);
        while(delim_str != NULL){
            current->next = (node*)malloc(sizeof(node)); 
            current = current->next;
            current->next = NULL;
            current->data  = atoi(delim_str);
            delim_str = strtok(NULL,delim);
            num_item++;
        }
        valid = 0;
        root =  head;

        // Checking for removing one element removal
        for(int i = 0; i < num_item + 1; i++){
            not_dec = 0;
            not_inc = 0;
            current_itt = 1;

            head = root;
            int past_val = head->data;
            head = head->next;

            // Checking for first element case
            if(i == 0 & num_item > 1){
                past_val = head->data;
                head = head->next;
                current_itt = 2;
            }
            // printf("%d ", past_val);
            // Iterating through the list
            while(head != NULL){
                // Checks distance
                if(abs(head->data - past_val) <= 3 && abs(head->data - past_val) >= 1){
                    if(head->data > past_val & current_itt != i){
                        not_dec = 1;
                    }
                    else if(head->data < past_val & current_itt != i){
                        not_inc = 1;
                    }
                }
                else if(current_itt != i){
                    not_inc = 1;
                    not_dec = 1;
                }
                // Updating the past value only if it isn't excluded
                if(current_itt != i){
                    past_val = head->data;
                }
                head = head->next;
                current_itt++;
            }
            if((not_dec || not_inc ) & !(not_dec & not_inc)){
                valid = 1;
            }
        }
        while(root != NULL){
            past = root;
            root = root->next;
            free(past);
        }
        if(valid == 1){
            count++;
        }
    }
    printf("The count is %d", count);
    return 1;
}