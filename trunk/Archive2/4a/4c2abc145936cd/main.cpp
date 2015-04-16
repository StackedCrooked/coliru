#include <iostream>
#include <cstdlib>
#include <vector>

enum ROW 
{
    R0 = 0,
    R1 = 1
};


enum COLUMN 
{
    C1 = 0,
    C2 = 1
}; 


int main()
{
    std::vector<std::vector<double>> alpha{ { 1.46774172175387E-005, 2.000064981},
                                        { 3.46774172175387E-005, 4.59485786231327E-005} };
                                        
    std::cout << alpha[ROW::R0][COLUMN::C1];
    return 0;
}