#include <iostream>
#include <locale>

struct put_new_line : std::num_put<char>
{
    iter_type do_put(iter_type s, std::ios_base& f, char_type fill, long v) const {
        auto x = std::num_put<char>::do_put(s, f, fill, v );
        dynamic_cast<std::ostream&>(f) << '\n';
        return x;
    }
    
    
    iter_type do_put(iter_type s, std::ios_base& f, char_type fill, unsigned long v) const {
        auto x = std::num_put<char>::do_put(s, f, fill, v);
        dynamic_cast<std::ostream&>(f) << '\n';
        return x;
    }
};
 
int main()
{
    std::cout.imbue(std::locale(std::cout.getloc(), new put_new_line));
    std::cout << 1 << 2 << 3;
}