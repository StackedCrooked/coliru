#include <string>

int main() 
{
    std::string s1;
    std::string s2(s1, s1.get_allocator());
}
