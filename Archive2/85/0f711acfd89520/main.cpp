#include <cassert>
#include <string>
 
int main()
{
    std::string s{ "Exemplar" };
    std::string::size_type const capacity = s.capacity();
 
    s.clear();
    assert(capacity == s.capacity());
    assert(s.empty());
    assert(0 == s.size());
}