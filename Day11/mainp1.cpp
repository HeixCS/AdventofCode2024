#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
signed long long number_of_digits(signed long long integer){
    signed long long mult = 10;
    signed long long count = 1;
    while(integer / 10 > 0){
        integer /= 10;
        count++;
    }
    return count;
}

using namespace std;
int main(void){
     // Opening and reading file
    ifstream myfile;
    myfile.open("input.txt");
    vector<signed long long> file_words;
    signed long long left, right, num_digits, mult;
    signed long long steps = 25;
    string line;
    char delim = ' ';
    while(getline(myfile, line,delim)){
        file_words.push_back(stoull(line));
    }
    for(signed long long k = 0 ; k < steps; k++){
        for(signed long long i = 0; i < file_words.size();i++){
            // Checking for 0
            if(file_words[i] == 0){
                file_words[i] = 1;
            }
            // Checking for even digits  
            else if(number_of_digits(file_words[i]) % 2 == 0){
                num_digits =  (number_of_digits(file_words[i]) / 2);
                mult = 1;
                // Can't use pow because it's imprecise
                for(int j = 0; j < num_digits; j++){
                    mult *= 10;
                }
                // Splitting the float 
                left = file_words[i] / mult;
                right = file_words[i] - left * mult;
                file_words[i] =  right;
                // Inserting it to the array
                file_words.insert(file_words.begin() + i,left);
                i++;
            }
            // The 3rd case of no rules apply
            else{
                file_words[i] *= 2024;
            }
        }
    }
    // for(int i = 0; i < file_words.size(); i++){
    //     cout << file_words[i]  << " ";
    // }
    cout << "The size is " << file_words.size();
}