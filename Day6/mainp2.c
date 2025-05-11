#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct play_area{
    int x_size;
    int y_size;
}PA;

typedef struct play_info{
    int x;
    int y;
}player;

typedef struct hurdle_info{
    int x;
    int y;
    int x_hurdle;
    int y_hurdle;
}hurdle;

typedef struct linked_list{
    hurdle data;
    struct linked_list* next;
}node;


void find_array_length(char*file_name, PA* input){
    // Opening file
    FILE* fp = fopen(file_name,"r");
    char buffer[1000] = {0};
    int count = 1;

    // Setting x size
    fgets(buffer,1000,fp);
    input->x_size = strlen(buffer) - 1;
    // Setting y size
    while(fgets(buffer,1000,fp) && buffer[0] != '\n'){
        count++;
    }
    input->y_size = count;
    fclose(fp);
    return;
}

int next_state_x(int x, int y){
    int player_x;
    if(x == 0){
        player_x = 1;
    }
    else{
        player_x =  0;
    }  
    if(y != 0){
        return player_x * (y);
    }
    else{
        return player_x;
    }
}

int next_state_y(int x, int y){
    int player_y;
    if(y == 0){
        player_y = 1;
    }
    else{
        player_y =  0;
    }
    if(x != 0){
        return player_y  * -x;
    }
    else{
        return player_y;
    }
}

int check_queue(node* queue, int x, int y, int x_hurdle, int y_hurdle){
    while(queue != NULL){
        // printf("Bug 4");
        // printf("Bug and %d and %d and %d and %d\n", queue->data.x, queue->data.y, queue->data.x_hurdle, queue->data.y_hurdle);
        if(queue->data.x == x && queue->data.y == y){
            if(queue->data.x_hurdle == x_hurdle && queue->data.y_hurdle == y_hurdle){
                return 1;
            }
        }
        queue = queue->next;
    }
    return 0;
}

void insert_queue(node** queue, int x, int y, int x_hurdle, int y_hurdle){
    if(*queue == NULL){
        // Making new node
        (*queue) = (node*)malloc(sizeof(node));
        (*queue)->data.x = x;
        (*queue)->data.y = y;
        (*queue)->data.x_hurdle = x_hurdle;
        (*queue)->data.y_hurdle = y_hurdle;
        (*queue)->next = NULL;
    }
    else{
        // Making new node
        node* next_node = (node*)malloc(sizeof(node));
        node *current = *queue;
        next_node->data.x = x;
        next_node->data.y = y;
        next_node->data.x_hurdle = x_hurdle;
        next_node->data.y_hurdle = y_hurdle;
        next_node->next = NULL;
        
        // Searching for tail of the queue
        while(current->next != NULL){
            current = current->next;
        }
        current->next = next_node;
    }
}

void free_queue(node*queue){
    node*previous;
    while(queue != NULL){
        previous = queue;
        queue = queue->next;
        free(previous);
    }
}

void initilize_map(char**map_copy,char**original_map, PA map_size){
    for(int i = 0; i < map_size.y_size;i++){
        map_copy[i] = (char*)malloc(map_size.x_size * sizeof(char));
        for(int j = 0; j < map_size.x_size;j++){
            map_copy[i][j] = original_map[i][j];
        }
    }
}
int check_cond_x(int x, int x_inc, PA map_size){
    int condx = x+x_inc != -1 & x+x_inc != map_size.x_size;
    return condx & (x != -1 & x != map_size.x_size);
}

int check_cond_y(int y, int y_inc, PA map_size){
    int condy = y-y_inc != -1 & y-y_inc != map_size.y_size;
    return condy & (y != -1 & y != map_size.y_size);
}

int place_obstruction(int player_x,int player_y, int x_increment, int y_increment, int condx, int condy, char** map1,PA map_size, int X_count){
    char**map = (char**)malloc(sizeof(char*)* map_size.y_size);
    initilize_map(map,map1,map_size);

    // Places the obstruction
    map[player_y - y_increment][player_x + x_increment] = 'O';
    
    // Making the linked list
    // node* head = (node*)malloc(sizeof(node));
    node* head = NULL;
    insert_queue(&head,player_x, player_y, player_x+x_increment,player_y - y_increment);

    // Rotate the player
    int prev_x;
    prev_x = x_increment;
    x_increment = next_state_x(x_increment,y_increment);
    y_increment = next_state_y(prev_x,y_increment);

    // Redefines the condition (checks if the next tile is at the end of the  map)
    condx = check_cond_x(player_x,x_increment,map_size);
    condy = check_cond_y(player_y,y_increment,map_size);

    // Goes till end of map
    while(condx & condy){
        // Checks next tile for hurdle
        // printf("Bug 1\n");
        while(map[player_y - y_increment][player_x + x_increment] == '#' | map[player_y - y_increment][player_x + x_increment] == 'O'){ 
            // printf("\noccurence %d,%d,%d, and %d\n",player_x,player_y,x_increment,y_increment);
            // Seeing if the hurdle was previously visited
            if(check_queue(head,player_x,player_y,player_x+x_increment,player_y-y_increment)){
                printf("\n__________________________\n");
                // Printing the map
                for(int i = 0; i < map_size.y_size;i++){
                    for(int j = 0; j < map_size.x_size;j++){
                        printf("%c",map[i][j]);
                    }
                    printf("\n");
                }
                printf("__________________________\n");

                // Freeing the map and queue
                free_queue(head);
                for(int i = 0; i < map_size.y_size;i++){
                    free(map[i]);
                }
                free(map);
                return 1;
                // }
            }
            // printf("Bug 6\n");
            // Adding hurdle to queue
            insert_queue(&head, player_x, player_y, player_x+x_increment, player_y-y_increment);
            // printf("Bug 7\n");
            // Updating the movement increment
            prev_x = x_increment;
            x_increment = next_state_x(x_increment,y_increment);
            y_increment = next_state_y(prev_x,y_increment);
            // Makes sure new increment isn't outside map
            condx = check_cond_y(player_x,x_increment,map_size);
            condy = check_cond_y(player_y,y_increment,map_size);
            // printf("\noccurence %d,%d,%d, and %d | %d and %d\n",player_x,player_y,x_increment,y_increment, condx, condy);
            if(!(condx & condy)){
                break;
            }
        }
        // printf("Bug9\n");
        // Marking the movement of the player
        if((map[player_y][player_x] == '^' | map[player_y][player_x] == '.') & (condx & condy)){
            map[player_y][player_x] = 'X';
        }
        player_x += x_increment;
        player_y -= y_increment;
        condx = check_cond_x(player_x,x_increment,map_size);
        condy = check_cond_y(player_y,y_increment,map_size);
        // printf("\nBug 5 %d and %d and %d and %d\n",condx,condy,player_x,player_y);
    }
    printf("\n__________FAIL__________\n");
    // Printing the map
    for(int i = 0; i < map_size.y_size;i++){
        for(int j = 0; j < map_size.x_size;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    printf("__________________________\n");

    // Freeing the map and queue
    free_queue(head);
    for(int i = 0; i < map_size.y_size;i++){
        free(map[i]);
    }
    free(map);
    return 0;
}

int main(void){
    char*input_file = "input.txt";
    PA map_size;
    player security_guard;
    int x_increment = 0, y_increment = 1, count = 0, prev_x = 0, x_count = 0;
    char buffer[1000];
    // Opening the file
    FILE*fp = fopen(input_file,"r");

    // Calculating the size of the map
    find_array_length(input_file,&map_size);
    printf("The x size is %d and y size is %d\n",map_size.x_size,map_size.y_size);
    
    // Creating array to store the map
    char**map = (char**)malloc(sizeof(char*)* map_size.y_size);
    for(int i = 0; i < map_size.y_size;i++){
        map[i] = (char*)malloc(map_size.x_size * sizeof(char));
        fgets(buffer,1000,fp);
        for(int j = 0; j < map_size.x_size;j++){
            map[i][j] = buffer[j];
            if(buffer[j] == '^'){
                security_guard.x = j;
                security_guard.y = i;
            }
        }
    }

    // Printing the map
    for(int i = 0; i < map_size.y_size;i++){
        for(int j = 0; j < map_size.x_size;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    
    int condx = check_cond_x(security_guard.x,x_increment,map_size);
    int condy = check_cond_y(security_guard.y,y_increment,map_size);
    while(condx & condy){
        if(map[security_guard.y - y_increment][security_guard.x + x_increment] == '#'){
            while(map[security_guard.y - y_increment][security_guard.x + x_increment] == '#'){ 
                prev_x = x_increment;
                x_increment = next_state_x(x_increment,y_increment);
                y_increment = next_state_y(prev_x,y_increment);
                condx = check_cond_y(security_guard.x,x_increment,map_size);
                condy = check_cond_y(security_guard.y,y_increment,map_size);
                if(!(condx & condy)){
                    break;
                }
            }
        }
        else{
            count+=place_obstruction(security_guard.x,security_guard.y,x_increment,y_increment,condx,condy,map,map_size,x_count);
        }
        if(map[security_guard.y][security_guard.x] == '^' | map[security_guard.y][security_guard.x] == '.'){
            map[security_guard.y][security_guard.x] = 'X';
        }
        security_guard.x += x_increment;
        security_guard.y -= y_increment;
        condx = check_cond_y(security_guard.x,x_increment,map_size);
        condy = check_cond_y(security_guard.y,y_increment,map_size);
        // printf("%d and %d | increment: %d and %d\n",security_guard.x,security_guard.y,x_increment,y_increment);
    }

    printf("The count is %d\n",count);
    // Freeing the map
    for(int i = 0; i < map_size.y_size;i++){
        free(map[i]);
    }
    free(map);
    fclose(fp);
    return 1;
}
