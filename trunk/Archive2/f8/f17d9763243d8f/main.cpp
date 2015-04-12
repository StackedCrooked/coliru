#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;
 
int main() {
    // Create input variables
    string line;
    vector<string> names;
    
    // Open File
    ifstream myfile("test.txt");
    
    // Populate the vector with each line
    while (getline(myfile, line))
    {
        names.push_back(line);
    }
    
    // Sort the vector
    sort(names.begin(), names.end());
    
    // Prep for file output
    ofstream outputfile;
    
    // Create output file sorted_names.txt
    outputfile.open ("sorted_names.txt");
    
    // Go through the vector and output the value
    for(auto name : names){
        outputfile << name << endl;
    }
    
    // Close the output file
    outputfile.close();
    
    return 0;
 
}