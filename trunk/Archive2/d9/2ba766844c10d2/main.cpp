#include <iostream>
#include <string>
#include <iterator>
#include <boost/tokenizer.hpp>

int main()
{
    std::string s = "ABCDEFGHIJK";

    int offsets[] = {3};
    boost::offset_separator f(offsets, offsets+1);
    typedef boost::token_iterator_generator<boost::offset_separator>::type Iter;

    std::string result;
    for(Iter i = boost::make_token_iterator<std::string>(s.begin(), s.end(), f); i != Iter(); ++i )
        if(i->size() == 3)
            result.append(i->rbegin(), i->rend());
        else
            result += *i;

    std::cout << result << '\n';
}
