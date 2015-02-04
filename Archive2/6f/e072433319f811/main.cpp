#include <iostream>
#include <fstream>
 
int main() 
{
    int ivalue;
    try {
        std::ifstream in("in.txt");
        in.exceptions(std::ifstream::failbit);
        in >> ivalue;
    } catch (std::ios_base::failure &fail) {
        // handle exception here
    }
}