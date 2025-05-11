#include <fstream>
#include <iostream>
#include <string>

int find_left_dot(std::string str){
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '.'){
            return i;
        }
    }
}

int find_right_digit(std::string str){
    for(int i = str.length() - 1; i >= 0; i--){
        if(str[i] != '.'){
            return i;
        }
    }
}

int main(void){
    int val, block = 1;
    long long final_sum = 0;
    int dot_ind,digit_ind;
    char file_id = 0;
    // Opening file and getting one line
    std::ifstream f("input.txt");
    std::string line;
    getline(f,line);

    // Making new string of ids and .
    std::string result_string = "";
    for(int i = 0;i < line.size(); i+=1){
        val = line[i] - '0';
        if(block){
            for(int i = 0; i < val; i++){
                result_string.append(std::to_string(file_id));
            }
            file_id++;
            block = 0;
        }
        else{
            for(int i = 0; i < val; i++){
                result_string.append(".");
            }
            block = 1;
        }
    }

    
    dot_ind = find_left_dot(result_string);
    digit_ind = find_right_digit(result_string);
    while(dot_ind < digit_ind){
        result_string[dot_ind] = result_string.at(digit_ind);
        result_string[digit_ind] = '.';
        dot_ind = find_left_dot(result_string);
        digit_ind = find_right_digit(result_string);        
    }
    // Calculating final sum
    for(int i = 0; i < result_string.length(); i++){
        if(result_string[i] == '.'){
            break;
        }
        final_sum += (result_string[i] - '0') * i;
    }
    std::cout << "The sum is " << final_sum << "\n";
    // Closing the file
    f.close();
    return 0;
}