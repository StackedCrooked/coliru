#include <ostream>
#include <fstream>
#include <iomanip>

int main()
{
   std::ofstream qFile("test");
   qFile << std::ios::left;
   qFile << std::setw(20);
}