#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;
 
int main() {
    // Create input variables
    // String Variable LINE will temporarily hold each row in the input file
    string line;
    
    // Defining the string vector NAMES that will hold the names from the text file
    vector<string> names;
    
    // Open the input file
    ifstream myfile("test.txt");
    
    // While loop will go through each row in the file and assign it to variable LINE
    while (getline(myfile, line))
    {
        // Expand the vector NAMES to add the current line being pass through the loop
        names.push_back(line);
    }
    
    // Sort the vector NAMES
    sort(names.begin(), names.end());
    
    // Prepare the file to output the sorted vector NAMES
    ofstream outputfile;
    
    // Create and open the output file "sorted_names.txt"
    outputfile.open ("sorted_names.txt");
    
    // Loop through the vector NAMES and output each entry to the txt file.
    for(auto name : names)
    {
        outputfile << name << endl;
    }
    
    // Close the output file
    outputfile.close();
    
    return 0;
}