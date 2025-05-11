#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
    std::vector<std::vector<unsigned long long>> result_string = {};
    std::vector<unsigned long long> gap_string = {}, block_string = {};

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

    // The file_id is just the final id of the block array
    file_id = block_string.size() - 1;
    
    // Adding all the blocks into the array
    for(int i = 0; i < block_string.size(); i++){
        digit_size = block_string[i];
        for(int j = 0; j < digit_size; j++){
            result_string[2 * i].push_back(i);
        }
    }   

    // Iterating through all the blocks
    for(int i = file_id; i >= 0; i--){
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
                gap_string[i - 1] += digit_size;
                
                // Swapping the digit values
                result_string[2 * i].clear();
                block_string[i] = 0;

                // Inserting the digits
                for(int k = 0; k < digit_size; k++){
                    result_string.at(2 * j + 1).push_back(i);
                }
                break;
            }
        }
    }
    unsigned long long current_val = 0;
    char* val_string = (char*)std::to_string(current_val).c_str();
    unsigned long long length = std::to_string(current_val).length();
    unsigned long long current_ind = 0;

    // Calculating final sum
    for(unsigned long long i = 0; i < result_string.size(); i++){
        // Checks if it is even (no gap)
        if(i % 2 == 0){
            for(int j = 0; j < result_string[i].size();j++){
                final_sum += result_string[i][j] * current_ind++;
            }
        }
        // If it is odd add the array then increment the file ids
        else{
            for(int j = 0; j < result_string[i].size();j++){
                final_sum += result_string[i][j] * current_ind++;
            }
            current_ind += gap_string[(i - 1) / 2];
        }
    }

    // Printing the final result
    std::cout << "The sum is " << final_sum << "\n";
    
    // Closing the file
    f.close();
    
    return 0;
}


// void print_result(std::vector<std::vector<unsigned long long>> result_string, std::vector<unsigned long long> block_string, std::vector<unsigned long long> gap_string){
//     for(int i = 0; i < result_string.size(); i++){
//         if((i % 2) == 0){
//             for(int j = 0; j < result_string[i].size(); j++){
//                 std::cout << result_string[i][j];
//             }
//         }
//         else if (i % 2 == 1){
//             for(int j = 0; j < result_string[i].size(); j++){
//                 std::cout << result_string[i][j];
//             }
//             try{
//                 // std::cout << std::endl << "value is "<< gap_string.at((i-1)/2) << std::endl;
//                 std::cout << std::string( gap_string.at((i - 1) / 2) ,'.');
//             }
//             catch(std::length_error){
//                 printf("\nThe error is %d and %d\n", (i-1) / 2, gap_string.size());
//                 printf("The size of the array is %d %d %d", result_string.size(), gap_string.size(), block_string.size());
//                 exit(-1);
//             }
//         }
//     }
//     std::cout << std::endl;
// }
