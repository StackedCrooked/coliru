#include <map>
#include <string>
#include <iostream>
#include <algorithm>

template<class BaseIterator>
struct key_iterator
    :public BaseIterator
{
    using base_type=BaseIterator;
    using base_type::base_type;
    
    base_type base()
    {
        return *this;
    }
};

template<class T>
key_iterator<typename T::value_type> make_key_iterator(T t)
{
    return t;
}

int main(int argc, char* argv[])
{
    std::map<std::string, int> m=
    {
        {"pina1", 1},
        {"pina2", 2},
        {"pina3", 3},
        {"pina4", 4},
    };
    
    auto res=std::find_if(make_key_iterator(m.begin()), make_key_iterator(m.end()), [](const std::string& s)
        {
            return s.back()=='3';
        });
        
    std::cout<<std::boolalpha<<(res.base().second==3)<<std::endl;

    return 0;
}