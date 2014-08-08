#include <string>
#include <iostream>

#include <boost/fusion/include/adapt_assoc_struct.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/deref_data.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>

namespace fusion = boost::fusion;

struct test
{
    test(const std::string& n, int v) : name(n), value(v) {}
    std::string name;
    int value;
    
    struct name_key { static const char* name() { return "name"; }};
    struct value_key { static const char* name() { return "value"; }};
};

struct test2
{
    test2(const std::string& s) : string(s) {}
    std::string string;
    
    struct string_key { static const char* name() { return "string"; }};
};

BOOST_FUSION_ADAPT_ASSOC_STRUCT
(
    test,
    (std::string, name, test::name_key)
    (int, value, test::value_key)
)

BOOST_FUSION_ADAPT_ASSOC_STRUCT
(
    test2,
    (std::string, string, test2::string_key)
)

template<typename Current, typename End>
struct print_helper
{
    static void apply(const Current& c)
    {
        std::cout << fusion::result_of::key_of<Current>::type::name() << " : " << fusion::deref_data(c) << std::endl;
        print_helper<typename fusion::result_of::next<Current>::type, End>::apply(fusion::next(c));
    }
};

template<typename End>
struct print_helper<End, End>
{
    static void apply(const End&) {}
};

template<typename T>
auto print(const T& object) -> decltype(fusion::begin(object), void())
{
    print_helper<typename fusion::result_of::begin<const T>::type, typename fusion::result_of::end<const T>::type>::
    apply(fusion::begin(object));
}

template<typename T>
auto print(const T& object) -> decltype(std::cout << object, void())
{
    std::cout << object << std::endl;
}

int main()
{
    test tst("this", 1);
    print(tst);
    test2 tst2("new");
    print(tst2);
}