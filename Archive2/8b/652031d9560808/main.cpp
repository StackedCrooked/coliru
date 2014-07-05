#include <iostream>
#include <string>

using namespace std;

struct loud_string : std::string
{
    loud_string() { std::cout << "loud_string default ctor\n"; }
    loud_string(char const* p) : string(p) { std::cout << "loud_string char const* ctor\n"; }
    loud_string(loud_string const& p) : string(p) { std::cout << "loud_string copy ctor\n"; }
    loud_string(loud_string&& p) : string(std::move(p)) { std::cout << "loud_string move ctor\n"; }
    ~loud_string() { std::cout << "loud_string dtor\n"; }
};

class string_view {
public:
    string_view(const loud_string& str)
        : _begin(str.data())
        , _end(str.data() + str.size()) {
        std::cout << "string_view(...)" << std::endl;
    }
    string_view(string_view const& p)
        : _begin(p._begin)
        , _end(p._end)
    { std::cout << "string_view copy ctor\n"; }
    
    ~string_view() { std::cout << "string_view dtor\n"; }

    const char* _begin;
    const char* _end;
};

void join(initializer_list<string_view> strings) {
    std::cout << "join(...)" << std::endl;
    for (auto i = 0u; i < 5; ++i) {
        std::cout << int(strings.begin()->_begin[i]) << " " << strings.begin()->_begin[i] << std::endl;
    }
}

int main() {
    join({ loud_string("this") });
    return 0;
}