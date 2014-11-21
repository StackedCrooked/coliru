#include <iostream>
#include <string>

class HtmlRover
{
public:
    HtmlRover(const std::string::const_iterator &, const std::string::const_iterator &);
    // ...
private:
    //...
    std::string::const_iterator _curIter;
    const std::string::const_iterator _offend;
    //...
};

HtmlRover::HtmlRover(const std::string::const_iterator & it1, const std::string::const_iterator & it2):
    _curIter(it1), _offend(it2)
{
}

int main()
{
    std::string foo("bar");
    HtmlRover f(foo.begin(), foo.end());
    
    return 0;
}