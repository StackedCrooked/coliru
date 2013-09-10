#include <string>

template<class S>
struct StringContainer
{};

template<class StringContainer>
void function(const StringContainer<std::string>& cont);

int main()
{
    StringContainer<std::string> s;
    function(s);
}
