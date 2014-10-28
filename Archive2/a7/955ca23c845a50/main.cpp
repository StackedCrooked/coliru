#include <map>
#include <string>
#include <iostream>
#include <algorithm>

template<class BaseIterator>
struct key_iterator
    :public std::iterator
    <
        std::forward_iterator_tag,
        typename std::iterator_traits<BaseIterator>::value_type::first_type
    >
{
    using base_type=BaseIterator;

    key_iterator(BaseIterator base)
        :base_{base}
    {}
    
    bool operator!=(const key_iterator& rhs) const
    {
        return base_!=rhs.base_;
    }
    
    key_iterator operator++()
    {
        return ++base_;
    }
    
    typename std::iterator_traits<key_iterator>::value_type operator*()
    {
        return base_->first;
    }

    base_type base()
    {
        return base_;
    }
    
private:
    BaseIterator base_;
};

template<class T>
key_iterator<T> make_key_iterator(T t)
{
    return {t};
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
        
    std::cout<<std::boolalpha<<(res.base()->second==3)<<std::endl;
    std::cout<<std::boolalpha<<(res.base()->second==2)<<std::endl;

    return 0;
}