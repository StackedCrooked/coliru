#include <cassert>
#include <string>
 
int main()
{
    std::string s;
    std::string::size_type new_capacity{ 100u };
    assert(new_capacity > s.capacity());
 
    s.reserve(new_capacity);
    assert(new_capacity <= s.capacity());
}