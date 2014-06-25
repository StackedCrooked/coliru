#include <iostream>
#include <initializer_list>
#include <sstream>
#include <utility>

constexpr struct endl_ {
    friend std::ostream& operator << (std::ostream& os, const endl_&) {
        os << '\n'; // << std::flush;
        return os;
    }
} endl;

template <class... Args>
void print(std::ostream& stream, Args&&... args)
{
    std::stringstream ss;
    std::initializer_list<int>{0, (void(ss << std::forward<Args>(args)), 0)...};
    stream << ss.rdbuf();
}

int main()
{
    print(std::cout, "The answer is ", 42, endl);
    //error: no matching function for call to 'print'
    print(std::cout, "The answer is NOT ", 13, endl);
}
