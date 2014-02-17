#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace foo {
    struct bar {
    };

    std::string to_string(bar) { return "foo::bar"; }
}

namespace {
    using std::to_string;

    std::string
    concat()
    {
        return "";
    }
    
    template<typename Head, typename... Tail>
    decltype( to_string(std::declval<Head>()) )
    concat(Head&& h, Tail&&... t);
    
    template<typename Head, typename... Tail>
    typename std::enable_if<
        std::is_same< std::string, decltype(std::string() + std::declval<Head>()) >::value, std::string
        >::type
    concat(Head&& h, Tail&&... t)
    {
        return std::forward<Head>(h) + concat(std::forward<Tail>(t)...);
    }
    
    template<typename Head, typename... Tail>
    decltype( to_string(std::declval<Head>()) )
    concat(Head&& h, Tail&&... t)
    {
        return to_string(std::forward<Head>(h)) + concat(std::forward<Tail>(t)...);
    }
}


int main()
{
    using std::cout;
    using std::endl;
    cout << concat("abc") << endl;
    cout << concat("abc", "def") << endl;
    cout << concat(std::string("abc"), "def") << endl;
    cout << concat(3) << endl;
    cout << concat("abc", 3) << endl;
    cout << concat(2, "abc", 4) << endl;
    cout << concat(2, "abc", 4, std::string("def")) << endl;
    cout << concat(foo::bar{}, "!!!") << endl;
}