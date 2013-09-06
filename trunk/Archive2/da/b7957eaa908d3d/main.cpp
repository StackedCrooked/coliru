#include <vector>
#include <string>

struct separated_range {
    static constexpr auto separator = ", ";
    
    separated_range(std::initializer_list<std::string> il)
        : items(il)
    {}
    
    std::vector<std::string> items;
    // Change the additional bookkeeping state as required
    bool pending_front_separator = false;
    bool pending_back_separator = false;
    
    std::string result() const
    {
        std::string r;
        if(pending_front_separator) r.append(separator);
        for(auto&& item: items) {
            r.append(item);
            r.append(separator);
        }
        if(!pending_back_separator) { r.pop_back(); r.pop_back(); }
        return r;
    }
    
    void chop_front(int n);
    void chop_back(int n);
};

bool operator==(separated_range const& lhs, std::string const& rhs)
{ return lhs.result() == rhs; }

constexpr const char* separated_range::separator;

template<typename... T>
separated_range R(T&&... t)
{ return { std::forward<T>(t)... }; }

#include <cassert>

int main()
{
    assert( R("1", "2", "3") == "1, 2, 3" );
    
    // chop_front
    {
        auto r = R("1", "2", "3");
        r.chop_front(1);
        assert( r == ", 2, 3" );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_front(2);
        assert( r == "2, 3" );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_front(1); r.chop_front(1);
        assert( r == "2, 3" );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_front(5);
        assert( r == "" );
    }
    
    // chop_back
    {
        auto r = R("1", "2", "3");
        r.chop_back(1);
        assert( r == "1, 2, " );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_back(2);
        assert( r == "1, 2" );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_back(1); r.chop_back(1);
        assert( r == "1, 2" );
    }
    
    {
        auto r = R("1", "2", "3");
        r.chop_back(5);
        assert( r == "" );
    }
}