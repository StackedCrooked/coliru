#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>


template <typename T, typename Pred>
void for_each(const T& t, const Pred& pred)
{
    for (typename T::size_type i = 0; i < t.size(); ++i)
        pred(t[i]);
}

void pred(char c)
{
    std::cout << c << " ";
}

int main()
{
    std::string s("the green red dog jumped over the flying potato.");
    for_each(s, pred);
    auto arr = { 1, 2, 3 };
    for_each(s, pred);
    
    return 0;
}