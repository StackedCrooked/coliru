#include <iostream>
#include <string>
#include <tuple>
 
struct S {
    int n;
    std::string s;
    float d;
    
    auto tie() const
    {
        return std::tie(n, s, d);
    }
    bool operator<(const S& rhs) const
    {
        return tie() < rhs.tie();
    }
    bool operator==(const S& rhs) const
    {
        return tie() == rhs.tie();
    }
    
};
 
int main()
{
    S s{42, "Test", 3.14f};
    std::cout << (s == s) << " " << (s < s) << std::endl;
}
