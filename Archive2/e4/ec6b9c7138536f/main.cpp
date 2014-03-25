#include <iostream>
#include <string>
#include <stdint.h>
#include <string.h>
#include <utility>
#include <assert.h>


#define ASSERT(cond) std::cout << __FILE__ << ":" << __LINE__ << "\"\"\t" #cond << "\"\"\t" << ((cond) ? "OK" : "FAIL") << std::flush << std::endl; assert(cond)




struct Range
{
    Range() : b(), e() {}
    Range(const char* b, const char* e) : b(b), e(e) {}
    Range(const std::string& s) : b(s.data()), e(s.data() + s.size()) {}
        
    const char* begin() const { return b; }
    const char* end() const { return e; }
    
    std::size_t size() const { return e - b; }
    bool empty() const { return size() == 0; }
    
    std::string to_string() const
    {
        return std::string(b, e);
    }
    
    const char* find(char c)
    {
        for (auto i = b; i != e; ++i)
        {
            if (c == *i)
            {
                return i;
            }
        }
        return e;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Range& range)
    {
        os << '[';
        for (auto c : range)
        {
            os << c;
        }
        return os << ']';
    }
    
    const char* b;
    const char* e;
};



// "a=1&b=2&c=3" => sets r to "b=2&c=3" and returns "a=1"
Range split(Range& r, char separator)
{
    // if source range is empty then return an empty range
    if (r.empty())
    {
        return Range();
    }
    
    for (auto i = r.begin(), e = r.end(); i != e; ++i)
    {
        if (*i == separator)
        {
            auto result = Range(r.b, i);
            r.b = i + 1;
            return result;
        }
    }
    
    // if separator not found then copy the source range into the result, clear the source range and return the result.
    auto result = r;
    r.b = r.e;
    return result;
}


int main()
{    
    {
        std::string str = "";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    } 
    {
        std::string str = "a=";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    } 
    {
        std::string str = "a=1";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    }
    {
        std::string str = "a=1&";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    }
    {
        std::string str = "a=1&b=";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    }
    {
        std::string str = "a=1&b=2";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    }
    {
        std::string str = "a=1&b=2&";
        Range all(str.data(), str.data() + str.size());        
        do
        {
            Range keyval = split(all, '&');
            Range key = split(keyval, '=');
            std::cout << "\"" << str << "\"\t" << key << " => " << keyval << std::endl;
            
        } while (!all.empty());
        std::cout << "---\n";
    }
    
}
