#include <algorithm>

typedef unsigned long long ullong;

void fill_matchstick_table(ullong (&table)[80]) {
    std::fill(table, table+80, 0ull);
    //seed the first digits
    //we don't seed zero, because it's not a leading digit
    //we'll add that right before the function ends
    //table[6] += 1; //0 takes 6 matches
    table[2] += 1; //1 takes 2 matches
    table[5] += 1; //2 takes 5 matches
    table[5] += 1; //3 takes 5 
    table[4] += 1; //4 takes 4 matches
    table[5] += 1; //5 takes 5 matches
    table[5] += 1; //6 takes 5 matches
    table[3] += 1; //7 takes 3 matches
    table[7] += 1; //8 takes 7 matches
    table[5] += 1; //9 takes 5 matches

    for(int i=4; i<80; ++i) {
        //deliberate use of a switch fallthrough
        switch(i) {
        default: table[i] += table[i-7]; //#####8 takes 7 matches
        case 6: 
        case 5: table[i] += table[i-5]*4; //#####2, ####5, ####6, ####9 each take 5 matches
        case 4: table[i] += table[i-4]; //####4 takes 4 matches
        case 3: table[i] += table[i-3]; //####7 takes 3 matches
        case 2: table[i] += table[i-2]; //####2 takes 2 matches
        case 1: 
        case 0: break;
        }
    }
    //now we add in that final zero
    table[6] += 1; //0 takes 6 matches
}

ullong find_matchstick_numbers(ullong (&table)[80], unsigned char input) {
    if (input < 80)
        return std::accumulate(table+0, table+input+1, 0ull);
    return -1;
}

#include <iostream>
#include <iterator>
#include <ctime>
int main() {
    clock_t begin = clock();
    ullong table[80];
    fill_matchstick_table(table);
    std::cout << "Using all of the matches:\n";
    for(int i=0; i<80; ++i)
        std::cout << i << " -> " << table[i] << '\n';
    std::cout << "Using any number of the matches:\n";
    for(int i=0; i<80; ++i)
        std::cout << i << " -> " << find_matchstick_numbers(table, i) << '\n';
    clock_t end = clock();
    double dur = double(end-begin)/CLOCKS_PER_SEC*1000;
    std::cout << "Took " << dur << "ms (" << (end-begin) << " ticks)\n";
}