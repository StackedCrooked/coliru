#include <cassert>
#include <iterator>
#include <string>
 
int main()
{
    std::string s("Ну ты ващще");
    assert(20 == s.size());
    assert(s.size() == s.length());
    assert(s.size() == static_cast<std::string::size_type>(
        std::distance(s.begin(), s.end())));
}