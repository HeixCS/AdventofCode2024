#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list{
    int data;
    struct linked_list* next;
}node;

int find_rule_length(char*file_name){
    FILE* fp = fopen(file_name,"r");
    char buffer[256] = {0};
    int count = 0;
    while(fgets(buffer,256,fp) && buffer[0] != '\n'){
        printf("%s\n", buffer);
        count++;
    }
    fclose(fp);
    return count;
}
const char delim = '|';
const char delim2 = ',';

int main(void){
    char* file_name = "input.txt",buffer[1000] = {0},*split_str;
    int rule_length = find_rule_length(file_name),array_elements = 0;
    int first_element,second_element,valid = 0, value = 0, count = 0;
    node*first_error,*second_error;
    printf("The rule length is %d\n", rule_length);

    int* arrayleft = (int*)malloc(sizeof(int) * rule_length);
    int* arrayright = (int*)malloc(sizeof(int) * rule_length);

    FILE* fp = fopen(file_name,"r");
    // Reading every line
    for(int i = 0; i < rule_length; i++){
        fgets(buffer,1000,fp);
        buffer[strlen(buffer)-1] = '\0';
        // Splitting each line 
        split_str = strtok(buffer,&delim);
        arrayleft[i] = atoi(split_str);
        split_str = strtok(NULL,&delim);
        arrayright[i] = atoi(split_str);
        printf("%d and %d\n", arrayleft[i],arrayright[i]);
    }
    // Deleting the space between rules and updates
    fgets(buffer,1000,fp);
    // Now reading all the arrays
    while(fgets(buffer,1000,fp)){
        array_elements = 1;
        valid = 1;
        // Makes the new head
        node*head = (node*)malloc(sizeof(node));
        head->data = atoi(strtok(buffer,&delim2));
        node*current = head;
        // Splits the spring and adds on elements to the tail
        while(split_str = strtok(NULL,&delim2)){
            node*next = (node*)malloc(sizeof(node));
            next->data = atoi(split_str);
            next->next = NULL;
            current->next = next;
            current = next;
            array_elements++;
        }
        // Printing every element
        current = head;
        while(current!=NULL){
            printf("%d ",current->data);
            current = current->next;
        }
        printf("\n");
        // Now considering each rule and making sure it's true
        for(int i = 0; i < rule_length;i++){
            first_element = arrayleft[i];
            second_element = arrayright[i];
            // Searching for the second element
            current = head;
            for(int i = 0; i < array_elements - 1;i++){
                // Sees if second element is in the array
                if(current->data == second_element){
                    // Marking the first element
                    first_error = current;
                    current = current->next;
                    // Searches the whole array
                    while(current != NULL){
                        if(current->data == first_element){
                            valid = 0;
                            break;
                        }
                        current=current->next;
                    }
                    break;
                }
                current = current->next;
            }
        }
        if(valid){
            value = array_elements / 2;
            current = head;
            for(int i = 0; i < value;i++){
                current = current->next;
            }
            count+=current->data;
        }
        while(head!=NULL){
            current = head->next;
            free(head);
            head = current;
        }
    }
    printf("\nThe sum is %d",count);
    free(arrayleft);
    free(arrayright);

    return 1;
}