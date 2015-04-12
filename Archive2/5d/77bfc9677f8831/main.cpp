#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
 
int main() {
    // Create input variables
    string line;
    vector<string> names;
    
    // Open File
    ifstream myfile("test.txt");
    
    // Check if file is open
    if (!myfile)
    {
        count << "Error opening the file" << endl;
        return -1;
    }
    
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
        myfile << name << endl;
    }
    
    // Close the output file
    outputfile.close();
    
    return 0;
 
}