#include <iostream>

#include <map>
#include <algorithm>

struct data
{
    int i;
    
    bool operator==(const data& b) const
    {
        return i == b.i;
    }
};

struct package
{
    typedef unsigned short   key_type;   
    typedef data             value_type;
    typedef std::map<key_type, value_type> list_t;
    
    bool isDefault;
    list_t list;
};


template<class T, class ForwardIterator>
auto FindMostCommon(const typename T::key_type& key, const ForwardIterator begin, const ForwardIterator end)
-> const typename T::value_type*
{
    struct Helper
    {
        typedef typename T::value_type TValue;
        
        const TValue* p;
        Helper(const TValue& v) { p = &v; }
        bool operator==(const Helper& v) const { return(*p == *v.p); }
        bool operator<(const Helper& v) const { return true; } 
    };
    
    typedef std::map<Helper, int> HelperMapT;
    typedef typename HelperMapT::value_type  HelperMapIt;
    HelperMapT counter;
    
    
    for(auto it = begin; it != end; ++it)
    {
        // todo dont exist
        counter[ Helper(it->list[key]) ] += 1;
    }
    
    std::cout << counter.size() << std::endl;
    for(auto it = counter.begin(); it != counter.end(); ++it)
        std::cout << it->first.p << " = " << it->second << std::endl;

    
    if(counter.size())
        return std::max_element(counter.begin(), counter.end(),
            [](const HelperMapIt& a, const HelperMapIt& b) { return(a.second < b.second); } )
            ->first.p;
    else
        return nullptr;
}


int main()
{
    std::array<package, 3> pack;
    
    pack[0].list[0].i = 10;
    pack[0].list[7].i = 20;
    pack[0].list[8].i = 30;
    
    pack[1].list[0].i = 66;
    pack[1].list[7].i = 10;
    pack[1].list[8].i = 11;
    
    pack[2].list[0].i = 90;
    pack[2].list[7].i = 20;
    pack[2].list[8].i = 90;
    
    std::cout << FindMostCommon<package>(7, pack.begin(), pack.end())->i << std::endl;
}



