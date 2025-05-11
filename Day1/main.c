#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct linked_list{
    int data;
    struct linked_list* next;
    int freq;
}node;

void insert(int data, struct linked_list list[]){
    // Hashing function
    int key = data % 100;
    node* head = &list[key];
    // Makes sure the bucket even has an element in it
    if(head == NULL){
        head =  (node*)malloc(sizeof(node));
        head->data = data;
        head->freq = 1;
        head->next = NULL;
    }
    else{
        // Iterates to theend of the list and makes sure there is no repeat 
        while(head->data!= data && head->next != NULL){
            head = head->next;
        }
        // If there is no repeat, make a new node
        if(head->data!= data){
            node* next =  (node*)malloc(sizeof(node));
            next->data  = data;
            head->next  =  next;
            next->freq = 1;
            next->next = NULL;
        }
        else{
            head->freq++;
        }
    }
}

int search(int data, struct linked_list list[]){
    // Hashing function
    int key = data % 100;
    node* head = &list[key];
    while(head->data!= data && head->next != NULL){
        head = head->next;
    }
    // if there is no repeat
    if(head->data!= data){
        return 0;
    }
    else{
        return head->freq;
    }

}

char* delim = "   ";

int main(void){
    node list_node[1000];
    FILE*Fp = fopen("./input.txt","r");
    if(!Fp){
        printf("The file was not opened");
        fclose(Fp);
    }
    
    int list1[1000] = {0},list2[1000] = {0};
    char buff[256], *delim_buffer;
    int n = 0, temp = 0;

    while(fgets(buff,256,Fp)){
        delim_buffer = strtok(buff,delim);
        list1[n] = atoi(delim_buffer);
        // printf("list1 is %s,",delim_buffer);
        delim_buffer = strtok(NULL,delim);
        list2[n] = atoi(delim_buffer);
        insert(list2[n],list_node);
        // printf("list1 is %d list2 is %d, and n is %d\n",list1[n],list2[n],n);
        n++;
    }
    for(int i = 0; i < 1000;i++){
        for(int j = 0; j < 999; j++){
            if(list1[j] < list1[j+1]){
                temp = list1[j];
                list1[j] = list1[j+1];
                list1[j+1] = temp;
            }
            if(list2[j] < list2[j+1]){
                temp = list2[j];
                list2[j] = list2[j+1];
                list2[j+1] = temp;
            }
        }
    }
    // for(int i = 0; i < 1000;i++){
    //     printf("list1 is %d list2 is %d\n",list1[i],list2[i]);
    // }
    int diff = 0, sim = 0;
    for(int i = 0; i < 1000; i++){
        diff += abs(list1[i] - list2[i]);
        sim  += list1[i] * search(list1[i],list_node);
        // printf("The value is %d and frequency is %d\n",list1[i],search(list1[i],list_node));
    }
    printf("The difference is %d\n", diff);
    printf("The similarity  is %d",sim);
    fclose(Fp);
    return 1;
}