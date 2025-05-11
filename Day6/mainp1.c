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

int main(void){
    char*input_file = "input.txt";
    PA map_size;
    player security_guard;
    int x_increment = 0, y_increment = 1, count = 1, prev_x = 0;
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
    
    int condx = security_guard.x + x_increment != -1 | security_guard.x + x_increment != map_size.x_size;
    int condy = security_guard.y - y_increment != -1 | security_guard.y - y_increment != map_size.y_size;
    while(condx & condy){
        if(map[security_guard.y - y_increment][security_guard.x + x_increment] == '#'){
            prev_x = x_increment;
            x_increment = next_state_x(x_increment,y_increment);
            y_increment = next_state_y(prev_x,y_increment);
        }
        if(map[security_guard.y][security_guard.x] == '^' | map[security_guard.y][security_guard.x] == '.'){
            map[security_guard.y][security_guard.x] = 'X';
            count++;
        }
        security_guard.x += x_increment;
        security_guard.y -= y_increment;
        condx = security_guard.x + x_increment != -1 & security_guard.x + x_increment != map_size.x_size;
        condy = security_guard.y - y_increment != -1 & security_guard.y - y_increment != map_size.y_size;
        printf("%d and %d | increment: %d and %d\n",security_guard.x,security_guard.y,x_increment,y_increment);
    }
    map[security_guard.y][security_guard.x] = 'X';

    // Printing the map
    for(int i = 0; i < map_size.y_size;i++){
        for(int j = 0; j < map_size.x_size;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
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
