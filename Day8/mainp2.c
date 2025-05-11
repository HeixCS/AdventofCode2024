#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Map holder
typedef struct{
    int x_size;
    int y_size;
    char** char_map;
}map;

// Coordinates holder
typedef struct{
    int x;
    int y;
}coords;

// Char holder and node
typedef struct char_obj_link{
    char character;
    int occurences;
    int curr_occurences;
    coords* list;
    struct char_obj_link* next;
}char_obj;

// Safely allocates memory
void* smalloc(int size){
    void* ret_val = malloc(size);
    if(ret_val){
        return ret_val;
    }
    else{
        printf("Malloc was not allocated!");
        exit(-1);
    }
}

// Searches the linked list if there is no previous occurence
void insert_node(char_obj** head, char character){
    if(*head != NULL){
        char_obj* prev = NULL;
        char_obj* current = (*head);
        while(current != NULL){
            if(current->character == character){
                current->occurences++;
                return;
            }
            prev = current;
            current = current->next;
        }
        prev->next = (char_obj*)smalloc(sizeof(char_obj));
        prev->next->character = character;
        prev->next->occurences = 1;
        prev->next->curr_occurences = 0;
        prev->next->next = NULL;
    }
    else{
        (*head) = (char_obj*)smalloc(sizeof(char_obj));
        (*head)->character = character;
        (*head)->occurences = 1;
        (*head)->curr_occurences = 0;
        (*head)->next  = NULL;
    }
}

void free_head(char_obj* head){
    char_obj* prev;
    // Makes sure the head isn't null
    if(head){
        while(head!=NULL){
            prev = (head);
            head = head->next;
            free(prev->list);
            free(prev);
        }
    }
}


// Safely opens file
void sfopen(FILE**fp, char* file_name,const char* mode){
    *fp = fopen(file_name,mode);
    if(*fp){
        return;
    }
    else{
        printf("The file does not exist");
        exit(-1);
    }
}

map allocate_map(char* file_name, char* mode){
    FILE*fp;
    char buffer[1000];
    map ret_val;
    ret_val.y_size = 1;

    // Finds the x and y length of the map
    sfopen(&fp,file_name,mode);
    fgets(buffer,1000,fp);
    ret_val.x_size = strlen(buffer) - 1;
    while(fgets(buffer,1000,fp)){
        ret_val.y_size++;
    }
    fclose(fp);
    
    // Allocating the y pointers
    ret_val.char_map = (char**)smalloc(sizeof(char*) * ret_val.y_size); 
    
    // Allocating the x pointers
    for(int i = 0; i < ret_val.y_size; i++){
        ret_val.char_map[i] = (char*)malloc(sizeof(char) * ret_val.x_size);
    }

    // Reading in the values
    sfopen(&fp,file_name,mode);
    for(int i = 0; i < ret_val.y_size; i++){
        fgets(buffer,1000,fp);
        for(int j = 0; j < ret_val.x_size; j++){
            ret_val.char_map[i][j] = buffer[j];
            printf("%c",ret_val.char_map[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return ret_val;
}

void populate_coords(char_obj* head, coords coordinate, char  character){
    while(head != NULL){
        if(head->character == character){
            head->list[head->curr_occurences++] = coordinate;
            return;
        }
        head = head->next;
    }
    printf("ERROR %c", character);
    exit(-1);
}
void populate_ll(char_obj* head, map char_map){
    char_obj* current = head;
    while(current != NULL){
        current->list = (coords*)smalloc(sizeof(coords) * current->occurences);
        current = current->next;
    }
    for(int i = 0; i < char_map.y_size; i++){
        for(int j = 0; j < char_map.x_size; j++){
            if(char_map.char_map[i][j] != '.'){
                coords curr = {j, i};
                populate_coords(head,curr,char_map.char_map[i][j]);
            }
        }
    }
}

int valid_coord(int coord, int coord_size){
    if((coord >= coord_size) || (coord < 0)){
        return 0;
    }
    else{
        return 1;
    }
}


void free_map(map* char_map){
    for(int i = 0; i < char_map->y_size; i++){
        free(char_map->char_map[i]);
    }
    free(char_map->char_map);
}

void alloc_anti_map(char***ret_map, map original){
    *ret_map = (char**)malloc(sizeof(char*) * original.y_size);
    for(int i = 0; i < original.y_size;i++){
        (*ret_map)[i] = (char*)malloc(sizeof(char) * original.x_size);
        for(int j = 0; j < original.x_size; j++){
            (*ret_map)[i][j] = '.';
        }
    }
}

void free_anti_map(char**char_map, map original){
    for(int i  = 0; i <  original.y_size; i++){
        free(char_map[i]);
    }
    free(char_map);
}

char* file_name = "input.txt";
char* mode = "r";


int main(void){
    int rise, run, occurences = 0, valid = 1, repeats = 1;
    coords left, right;
    // Creating the map from the input file
    map read_map = allocate_map(file_name,mode);
    
    // Making anti  map
    char **anti_map = NULL;
    alloc_anti_map(&anti_map,read_map);

    // Declaring the queue
    char_obj* head = NULL;
    for(int i = 0; i < read_map.y_size; i++){
        for(int j = 0; j < read_map.x_size; j++){
            if(read_map.char_map[i][j] != '.'){
                insert_node(&head,read_map.char_map[i][j]);
            }
        }
    }   
    // Sets the arrays for each character
    populate_ll(head,read_map);
    
    //Now trying every possible combination
    char_obj* current = head;
    while(current !=  NULL){
        for(int i = 0; i < current->occurences; i++){
            for(int j = i + 1; j < current->occurences; j++){
                // Calculates the different between two points
                rise = current->list[j].y - current->list[i].y;
                run = current->list[j].x - current->list[i].x;
                repeats = 0;
                valid = 1;
                while(valid){
                    valid = 0;
                    left.x = current->list[j].x + run * repeats;
                    left.y = current->list[j].y + rise * repeats;
                    right.x = current->list[i].x - run * repeats;
                    right.y = current->list[i].y - rise * repeats++;
                    if(valid_coord(left.x, read_map.x_size) && valid_coord(left.y, read_map.y_size)){
                        if(read_map.char_map[left.y][left.x] == '.'){
                            read_map.char_map[left.y][left.x] = '#';
                        }
                        if(anti_map[left.y][left.x] == '.'){
                            anti_map[left.y][left.x] = '#';
                            occurences++;
                        }
                        valid = 1;
                    }
                    if(valid_coord(right.x, read_map.x_size)  && valid_coord(right.y, read_map.y_size)){
                        if(read_map.char_map[right.y][right.x] == '.'){
                            read_map.char_map[right.y][right.x] = '#';
                        }
                        if(anti_map[right.y][right.x] == '.'){
                            anti_map[right.y][right.x] = '#';
                            occurences++;
                        }
                        valid = 1;
                    }
                }
            }
        }
        current = current->next;
    }
    // Printing out the final result
    printf("\n\n\n");
    for(int i = 0; i < read_map.y_size; i++){
        for(int j =0; j < read_map.x_size; j++){
            printf("%c",read_map.char_map[i][j]);
        }
        printf("\n");
    }
    printf("The number of occurences is %d\n", occurences);

    // Freeing the map and linked list
    free_anti_map(anti_map,read_map);
    free_map(&read_map);
    free_head(head);
    return 1;
}