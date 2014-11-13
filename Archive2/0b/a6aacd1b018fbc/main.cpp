#include <fstream>
#include <istream>
#include <ostream>

int main() 
{
    {
        std::ofstream ofs("/tmp/lightness");
        ofs << "hi";
    }
    
    {
        std::ofstream ofs("/tmp/lightness", std::ios_base::trunc);
        ofs << "Data";
    }
}