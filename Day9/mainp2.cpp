#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

unsigned long long find_left_dot(std::vector<std::string> str, unsigned long long starting_ind){
    for(unsigned long long i = starting_ind; i < str.size(); i++){
        if(str[i] == "."){
            return i;
        }
    }
}

unsigned long long find_left_dot_size(std::vector<std::string> str, unsigned long long ind){
    unsigned long long size = 1;
    for(unsigned long long index = ind + 1; index < str.size(); index++){
        if(str[index] != "."){
            break;
        }
        size++;
    }
    return size;
}

unsigned long long find_right_digit_size(std::vector<std::string> str, unsigned long long ind){
    unsigned long long size = 1;
    std::string current = str[ind];
    for(unsigned long long index = ind - 1; index >= 0; index--){
        if(str[index] != current){
            break;
        }
        size++;
    }
    return size;
}

unsigned long long find_right_digit(std::vector<std::string> str, std::string integer){
    unsigned long long initial = str.size() - 1;
    for(unsigned long long i = initial; i >= 0; i--){
        if(str[i] == integer){
            return i;
        }
    }
}

int main(void){
    // 
    unsigned long long val, block = 1;
    unsigned long long final_sum = 0;
    unsigned long long dot_ind,digit_ind;
    unsigned long long file_id = 0, dot_size = 0, digit_size = 0;

    // Opening file and getting one line
    std::ifstream f("input.txt");
    std::string line;
    getline(f,line);

    // Making new string of ids and .
    std::vector<std::string> result_string = {};
    
    // Creating the string
    for(int i = 0;i < line.size(); i++){
        val = line[i] - '0';
        if(block){
            for(int i = 0; i < val; i++){
                result_string.push_back(std::to_string(file_id));
            }
            file_id++;
            block = 0;
        }
        else{
            for(int i = 0; i < val; i++){
                result_string.push_back(".");
            }
            block = 1;
        }
    }
    // Fixing file_id
    file_id--;
    for(int i = file_id; i >= 0; i--){
        // Finding the index of the file id and first empty block
        digit_ind = find_right_digit(result_string,std::to_string(i));
        dot_ind = find_left_dot(result_string,0);
        // Calculating sizes of both blocks
        digit_size = find_right_digit_size(result_string,digit_ind);
        dot_size = find_left_dot_size(result_string,dot_ind);
        // Skipping an empty block if it's too small then iterating till it's big enough of if the string has ended
        while(dot_ind < digit_ind && dot_size < digit_size){
            dot_ind += dot_size;
            dot_ind = find_left_dot(result_string,dot_ind);
            dot_size = find_left_dot_size(result_string,dot_ind);
        }

        // Checks if the end of string was reached
        if(dot_ind >= digit_ind){
            digit_size = 0;
        }
        // Swaps all the values
        for(int i = 0; i < digit_size; i++){
            std::swap(result_string[dot_ind + i],result_string[digit_ind - i]);
        }
    }

    // Calculating final sum
    for(unsigned long long i = 0; i < result_string.size(); i++){
        if(result_string[i] == "."){
            continue;
        }
        final_sum += stoull(result_string[i]) * i;
    }

    for(int i = 0; i < result_string.size(); i++){
        std::cout << result_string.at(i);
    }
    std::cout << std::endl;

    // Printing the final result
    std::cout << "The sum is " << final_sum << "\n";
    
    // Closing the file
    f.close();
    
    return 0;
}