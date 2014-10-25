#include <boost/utility/string_ref.hpp>
#include <cassert>

template <size_t N>
struct fixed_string : boost::string_ref {
    fixed_string() : boost::string_ref(storage_.begin(), 0) { }

    template <size_t M>
    fixed_string(char const (&s)[M]) 
        : boost::string_ref(storage_.begin(), M-1)
    {
        static_assert(M<=N+1, "capacity exceeded");
        assert(!s[M]);
        std::copy(s, s+(M-1), storage_.begin());
    }

  private:
    boost::array<char, N> storage_;
};

#include <iostream>

int main()
{
    fixed_string<32> demo;
    demo = "hello";

    std::cout << "fs: '" << demo << "'\n";
    demo = "world!";
    std::cout << "fs: '" << demo << "'\n";

}