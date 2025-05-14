#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include  <bits/stdc++.h>
using namespace std;

void recursive_search(vector<string> map, long coordinate_x, long coordinate_y, long* x_size, long* y_size, vector<pair<long, long>> *end_points);

long count_trail = 0;

int main(void){
    // Opening and reading file
    ifstream myfile;
    myfile.open("input.txt");
    vector<string> file_lines;
    string line;
    while(getline(myfile, line)){
        file_lines.push_back(line);
    }
    // Assigning size of the map
    long x_size = file_lines[0].length();
    long y_size = file_lines.size();

    // Array to store coordinates(x,y) of trail ends
    vector<pair<long, long>> end_points = {};

    // Finding all the trail heads
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            if(file_lines[i][j] == '0'){
                end_points.clear();
                // Starting the recursive search
                recursive_search(file_lines,j,i,&x_size, &y_size, &end_points);
            }
        }
    }
    cout << "The count is " << count_trail;
    myfile.close();
    return 0;
}
// Needs previous value, coordinate, x_size, y_size and previous visited nodes
void recursive_search(vector<string> map, long coordinate_x, long coordinate_y, long* x_size, long* y_size, vector<pair<long, long>> *end_points){
    // End Condition
    if(map[coordinate_y][coordinate_x] == '9'){
        pair<long,long> coords = {coordinate_x,coordinate_y};
        if(find((*end_points).begin(), (*end_points).end(), coords) == (*end_points).end()){
            count_trail++;
            (*end_points).push_back(move(coords));
            return;
        }
    }
    // Checks left
    if((coordinate_x - 1) >= 0){
        if(map[coordinate_y][coordinate_x - 1] - map[coordinate_y][coordinate_x] == 1){
            recursive_search(map,coordinate_x-1,coordinate_y,x_size,y_size, end_points);
        }
    }
    // Checks right
        if((coordinate_x + 1) < (*x_size)){
        if(map[coordinate_y][coordinate_x + 1] - map[coordinate_y][coordinate_x] == 1){
            recursive_search(map,coordinate_x+1,coordinate_y,x_size,y_size, end_points);
        }
    }
    // Check Down
    if((coordinate_y + 1) < (*y_size)){
        if(map[coordinate_y + 1][coordinate_x] - map[coordinate_y][coordinate_x] == 1){
            recursive_search(map,coordinate_x,coordinate_y+1,x_size,y_size, end_points);
        }
    }
    // Checks left
    if((coordinate_y - 1) >= 0){
        if(map[coordinate_y - 1][coordinate_x] - map[coordinate_y][coordinate_x] == 1){
            recursive_search(map,coordinate_x,coordinate_y-1,x_size,y_size, end_points);
        }
    }
}