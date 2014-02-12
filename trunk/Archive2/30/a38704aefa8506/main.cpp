/* 
 * File:   main.cpp
 * Author: Jonny
 *
 * Created on 09 February 2014, 13:58
 */

#include <cstdlib>
#include <iostream>

#include "SurnameChecker.h"

using namespace std;

/*
 *
 */
void printCorrectUsage(char* arg) {
    fprintf(stderr, "Usage: %s <surname(s)> < <filename>\n", arg);
    fprintf(stderr, "E.g. %s Jones Winston < surnames.txt\n", arg);
    exit(1);
}



/*
 * The main method.
 * This is the entry point to the program.
 */
int main(int argc, char** argv) {

    /*
     * Ensure that enough parameters have been supplied.
     * The minimum number of parameters is 4, for example, in the case of:
     * ./executablefile Jones < surnames.txt
     */
    if (argc < 2) {
        fprintf(stderr, "Error: Not enough parameters supplied!\n");
        printCorrectUsage(argv[0]);
    }    
    
    SurnameChecker aSurnameChecker;
    /*
    if (!aSurnameChecker.fileOpenedSuccessfully()){
        fprintf(stderr, "Error: File %s not found!\n", argv[argc-1]);
        exit(1);
    }
    */
    
    /*
     * Output the phonetic matches for each surname.
     * Loop through the program's args, starting at the index of the first query surname (2).
     */
    for (int currentSurnamePosition = 1; currentSurnamePosition < argc; currentSurnamePosition++){
        
        cout << argv[currentSurnamePosition] << ": "; 
        cout.flush();
        vector<string> matches = aSurnameChecker.getMatches(argv[currentSurnamePosition]);
        
        //cout << matches.size() << endl;
        
        for (int currentMatch = 0; currentMatch < matches.size(); currentMatch++){
            if (currentMatch > 0) {
                //cout << ", ";
                //cout.flush();
            }
            
            cout << matches[currentMatch];
            cout.flush();
        }
        
        cout << endl << endl;
        
    }
    
    return 0;
}

