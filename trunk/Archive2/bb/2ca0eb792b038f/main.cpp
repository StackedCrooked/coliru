#include <string>


int main()
{
    std::string s;
    std::string t(s, s.get_allocator());
}
