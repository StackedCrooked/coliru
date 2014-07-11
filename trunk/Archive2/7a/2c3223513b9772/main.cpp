#include <vector>
int main()
{
std::vector<unsigned short int> list = {1}; 
unsigned short int one = 1;
 
one += list.at(0);                            // produces warning
one += 1;                                     // produces warning
one += static_cast<unsigned short int>(1);     // produces warning
one++;  
}