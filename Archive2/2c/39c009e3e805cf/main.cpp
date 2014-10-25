#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main(int arc, char* argv[]){
    std::ifstream in("dictionary.txt");
    
    // read all the words from the file:
    std::vector<std::string> dictionary;
    for(std::string x; in >> x;)
        dictionary.push_back(x);
    
    // If the words might not already be sorted, sort them:
    // std::sort(dictionary.begin(), dictionary.end());
    
    // open the file to check:
    std::ifstream check(argv[2]);
    
    // print out the words that aren't in the dictionary:
    for(std::string x; check >> x; )
        if( ! binary_search(begin(dictionary), end(dictionary), x) )
                std::cout << x << "\n";
}