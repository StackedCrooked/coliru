#include <iostream>
#include <string>
#include <stdint.h>
#include <string.h>
#include <utility>
#include <assert.h>


#define ASSERT(cond) std::cout << __FILE__ << ":" << __LINE__ << ": " #cond << ": " << ((cond) ? "OK" : "FAIL") << std::flush << std::endl; assert(cond)




struct range
{
    range() : b(), e() {}
    range(const char* b, const char* e) : b(b), e(e) {}
    range(const std::string& s) : b(s.data()), e(s.data() + s.size()) {}
        
    const char* begin() const { return b; }
    const char* end() const { return e; }
    
    std::size_t size() const { return e - b; }
    bool empty() const { return size() == 0; }
    
    std::string to_string() const
    {
        return std::string(b, e);
    }
    
    const char* b;
    const char* e;
};


// "abc=123" => range(abc, abc + 3), 
// "abc=" => 
std::pair<range, range> parse_keyval(range r)
{
    std::pair<range, range> result;
    
    for (auto i = r.begin(), e = r.end(); i != e; ++i)
    {
        char c = *i;
        if (c == '=')
        {
            result.first.b = r.begin();
            result.first.e = i;
            result.second.b = i + 1;
            result.second.e = r.end();
            return result;
        }
    }
    
    // empty
    return result;
}


// "a=1&b=2&c=3" =>  returns range for "b=2&c=3"
// "b=2" => returns empty range
// "" => returns empty range
range next_keyval(range r)
{
    for (auto i = r.begin(), e = r.end(); i != e; ++i)
    {
        if (*i == '&')
        {
            return range(i + 1, e);
        }
    }
    return range();
}



int main()
{    
    {
        auto pair = parse_keyval(std::string("a=1"));
        auto key = pair.first;
        ASSERT(!key.empty());
        ASSERT(key.to_string() == "a");
        
        auto value = pair.second;
        ASSERT(!value.empty());
        ASSERT(value.size() == 1);
        ASSERT(value.to_string() == "1");
    }
    
    {
        auto pair = parse_keyval(std::string("a="));
        auto key = pair.first;
        ASSERT(!key.empty());
        ASSERT(key.to_string() == "a");
        
        auto value = pair.second;
        ASSERT(value.empty());
        ASSERT(value.size() == 0);
        ASSERT(value.to_string() == "");
    }
    
    {
        auto pair = parse_keyval(std::string(""));
        ASSERT(pair.first.empty());
        ASSERT(pair.second.empty());
    }
    
    {
        std::string values = "a=1&b=2";
        range next = next_keyval(range(values));
        ASSERT(next.to_string() == "b=2");
    }
    
    {
        std::string values = "b=2";
        range next = next_keyval(range(values));
        ASSERT(next.empty());
    }
}

