#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
unsigned long long find_left_dot(std::vector<std::string> str){
    unsigned long long initial = 0;
    for(unsigned long long i = initial; i < str.size(); i++){
        if(str[i] == "."){
            initial = i;
            return i;
        }
    }
}

unsigned long long find_right_digit(std::vector<std::string> str){
    unsigned long long initial = str.size() - 1;
    for(unsigned long long i = initial; i >= 0; i--){
        if(str[i] != "."){
            initial = i;
            return i;
        }
    }
}

int main(void){
    // __uint128 integer = 5;/
    unsigned long long val, block = 1;
    unsigned long long final_sum = 0;
    unsigned long long dot_ind,digit_ind;
    unsigned long long file_id = 0;
    // Opening file and getting one line
    std::ifstream f("input.txt");
    std::string line;
    getline(f,line);

    // Making new string of ids and .
    std::vector<std::string> result_string = {};

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
    
    dot_ind = find_left_dot(result_string);
    digit_ind = find_right_digit(result_string);
    while(dot_ind < digit_ind){
        std::swap(result_string[dot_ind],result_string[digit_ind]);
        dot_ind = find_left_dot(result_string);
        digit_ind = find_right_digit(result_string);        
    }
    // // Calculating final sum
    for(unsigned long long i = 0; i < result_string.size(); i++){
        // std::cout << result_string[i];
        std::cout << final_sum << "\n";
        if(result_string[i] == "."){
            break;
        }
        final_sum += stoull(result_string[i]) * i;
    }
    std::cout << "The sum is " << final_sum << "\n";
    // Closing the file
    f.close();
    return 0;
}