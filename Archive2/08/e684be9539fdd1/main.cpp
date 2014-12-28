#include <iostream>
#include <fstream>
#include <cstdlib>
int main()
{
    std::ifstream file("test.txt");
    if(!file)  // operator! is used here
    {  
        std::cout << "File opening failed\n";
        return EXIT_FAILURE;
    }
 
    // typical C++ I/O loop uses the return value of the I/O function
    // as the loop controlling condition, operator bool() is used here
    for(int n; file >> n; ) {
       std::cout << n << ' ';
    }
    std::cout << '\n';
 
    if (file.bad())
        std::cout << "I/O error while reading\n";
    else if (file.eof())
        std::cout << "End of file reached successfully\n";
    else if (file.fail())
        std::cout << "Non-integer data encountered\n";
}