#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <chrono>
#include <array>
// Functions
long long reccur_blink(long long val, long long step);
inline long long number_of_digits( long long integer);

using namespace std;

// Global Variables
long long count_stone = 0;
const long long fill_val = 0;
const long long cache_size = 1000;
// Number of Blinks
const long long steps = 75;
array<array<long long, cache_size>, steps> cache;


int main(void){
    // Checking execution time
    auto start = chrono::high_resolution_clock::now();

    // Opening and reading file
    ifstream myfile;
    myfile.open("input.txt");
    vector< long long> file_words;
    string line;
    char delim = ' ';
    while(getline(myfile, line,delim)){
        file_words.push_back(stoll(line));
    }
    // Reserving space for algorithm
    for(int i = 0; i < cache.size(); i++){
        fill(begin(cache[i]),end(cache[i]),fill_val);
    }

    for( long long i = 0; i < file_words.size();i++){
        count_stone += reccur_blink(file_words[i],steps);
    }

    myfile.close();
    // Program is over
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "The size is " << count_stone << "\n";
    cout << "The duration is " << duration.count() << "\n";
}

long long reccur_blink(long long val, long long step){
    pair<long long, long long> hash_val;
    long long num_digits, mult, left, right;
    // cout << "value is " << val << endl;
    // Ends recursion
    if(step == 0){
        // cout << "value is " << val << endl;
        return 1;
    }
    if(val < cache_size && cache[step-1][val] != 0){
        // cout << "VALUE IS FOUND " << cache[step-1][val]  << endl;
        return cache[step-1][val];
    }
    // Checking for 0
    if(val == 0){
        cache[step-1][val] = reccur_blink(1,step - 1);
        // cout << "count is " << cache[step-1][val] << "\n";
        return cache[step-1][val];
    }

    num_digits = number_of_digits(val);
    // Checking for even digits  
    if(num_digits % 2 == 0){
        num_digits /= 2;
        mult = 1;
        // Calculating  the power
        // Can't use pow because it's imprecise
        for( long long j = 0; j < num_digits; j++){
            mult *= 10;
        }
        // Splitting the float 
        left = val / mult;
        right = val - left * mult;

        // Adding to the cache if there is space
        if(val < cache_size){
            cache[step-1][val] = reccur_blink(left,step - 1) + reccur_blink(right, step - 1);
            // cout << "count is " << cache[step-1][val] << "\n";
            return cache[step-1][val];
        }
        return reccur_blink(left,step - 1) + reccur_blink(right, step - 1);
    }
    // The 3rd case of no rules apply
    else{
        if(val < cache_size){
            cache[step-1][val] = reccur_blink(move(val * 2024LL), step - 1);
            // cout << "count is " << cache[step-1][val] << "\n";
            return cache[step-1][val];
        }
        return reccur_blink(move(val * 2024LL), step - 1);
    }
}

inline long long number_of_digits( long long integer){
    return llround(ceil(log10(integer + 0.5)));
}