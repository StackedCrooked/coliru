#include <fstream>
#include <iostream>
#include <cstdlib>

// This transformation function will turn spaces into X's
static char transform_char(char c) {
    if (c == ' ') {
        return 'X';
    } else {
        return c;
    }
}

int main(int argc, char *argv[]) {
    // Check that the user is running the program correctly:
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file>\n";
        return EXIT_FAILURE;
    }

    // Open the file indicated by the user when they ran the command
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error: unable to open file \"" << argv[1] << "\" for reading.\n";
        return EXIT_FAILURE;
    }
    
    // Open a file to write the results to. You can open more than one file this way.
    std::ofstream output("output.txt");
    if (!output) {
        std::cout << "Error: unable to open file output.txt for writing.\n";
        return EXIT_FAILURE;
    }
    
    // a loop to get each character from the input file, transform it
    // using a function, and write the resulting character to the output file.
    char c;
    while (input.get(c)) {
        output.put(transform_char(c));
    }
    return EXIT_SUCCESS;
}
