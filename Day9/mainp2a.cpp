#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

void print_result(std::vector<unsigned long long> result_string, std::vector<unsigned long long> block_string, std::vector<unsigned long long> gap_string){
    for(int i = 0; i < result_string.size(); i++){
        if(i == 0){
            std::cout << std::string(block_string[0],'0');
        }
        else if((i % 2) == 0 && result_string.at(i) != 0){
            std::cout <<result_string.at(i);
        }
        else if (i % 2 == 1){
            if(result_string.at(i) != 0){
                std::cout << result_string.at(i);
            }
            try{
                // std::cout << std::endl << "value is "<< gap_string.at((i-1)/2) << std::endl;
                std::cout << std::string( gap_string.at((i - 1) / 2) ,'.');
            }
            catch(std::length_error){
                printf("\nThe error is %d and %d\n", (i-1) / 2, gap_string.size());
                printf("The size of the array is %d %d %d", result_string.size(), gap_string.size(), block_string.size());
                exit(-1);
            }
        }
    }
    std::cout << std::endl;
}

std::string return_result(std::vector<unsigned long long> result_string, std::vector<unsigned long long> block_string, std::vector<unsigned long long> gap_string){
    std::string result = std::string("");
    for(int i = 0; i < result_string.size(); i++){
        if(i == 0){
            result += std::string(block_string[i],'0');
        }
        else if((i % 2) == 0 && result_string.at(i) != 0){
            result += std::to_string(result_string.at(i));
        }
        else if (i % 2 == 1){
            if(result_string.at(i) != 0){
                result += std::to_string(result_string.at(i));
            }
            result += std::string( gap_string[(i - 1) / 2] ,'.');
        }
    }
    return result;
}

unsigned long long find_multiplier(unsigned long long integer){
    unsigned long long mult = 10;
    while(mult < integer){
        mult *= 10;
    }
    return mult;
}

int main(void){
    unsigned long long val, block = 1;
    unsigned long long final_sum = 0, multiplier = 0;
    unsigned long long dot_ind,digit_ind;
    unsigned long long file_id = 0, dot_size = 0, digit_size = 0;

    // Opening file and getting one line
    std::ifstream f("input.txt");
    std::string line;
    getline(f,line);

    // Making new string of ids and .
    std::vector<unsigned long long> result_string = {}, gap_string = {}, block_string = {};
    // Creating the gap and block string
    for(int i = 0;i < line.size(); i++){
        val = line[i] - '0';
        if(block){
            block_string.push_back(val);
            block = 0;
        }
        else{
            gap_string.push_back(val);
            block = 1;
        }
    }
    // Setting size the vector and setting it to 0
    result_string.resize(gap_string.size() + block_string.size());
    std::fill(result_string.begin(),result_string.end(), 0);

    // The file_id is just the final id of the block array
    file_id = block_string.size() - 1;
    
    // Adding all the blocks into the array
    for(int i = 0; i < block_string.size(); i++){
        digit_size = block_string[i];
        multiplier = find_multiplier(i);
        for(int j = 0; j < digit_size; j++){
            result_string[2 * i] = result_string[2 * i] * multiplier + i;
        }
    }   
    print_result(result_string,block_string,gap_string);

    // Iterating through all the blocks
    for(int i = file_id; i >= 0; i--){
        // print_result(result_string,block_string,gap_string);
        // Calculating sizes of both blocks
        digit_size = block_string[i];
        
        // Going through Gap sizes
        for(int j = 0; j < gap_string.size(); j++){
            dot_size = gap_string[j];
            // Checking if the gap is before the digit
            if(2 * j + 1 > 2 * i){
                break;
            }
            // Find the correct size block
            if(dot_size >= digit_size && dot_size != 0){
                // swapping the dot values
                gap_string[j] -= digit_size;
                gap_string[i - 1]+= digit_size;
                // Swapping the digit values
                result_string[2 * i] = 0;
                block_string[i] = 0;

                // Inserting the digits
                multiplier = find_multiplier(i);
                for(int k = 0; k < digit_size; k++){
                    result_string.at(2 * j + 1) = (result_string[2 * j + 1] * multiplier) + i;
                }
                break;
            }
        }
    }
    // Converting to string
    std::string result = return_result(result_string,block_string,gap_string);

    // Calculating final sum
    for(unsigned long long i = 0; i < result.length(); i++){
        if(result[i] == '.'){
            continue;
        }
        final_sum += (result[i] - '0' )* i;
    }
    std::cout << result << std::endl;
    // Printing the final result
    std::cout << "The sum is " << final_sum << "\n";
    
    // Closing the file
    f.close();
    
    return 0;
}