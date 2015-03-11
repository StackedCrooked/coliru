#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/preprocessor.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/copy_if.hpp>

template <typename S1, typename S2>
struct Concatenate {
    typedef typename boost::mpl::copy_if<
            S2,
            boost::mpl::not_<
                boost::is_same<
                    boost::mpl::_1,
                    boost::mpl::integral_c<char, '\0'>>
            >,
            boost::mpl::back_inserter< S1 >
    >::type type;
};

// sink template parameter _ simplifies AT macro
template<typename _, char ... CHARS>
struct StaticString {
private:
    typedef typename boost::mpl::vector_c<char, CHARS...>::type _input;
public:
    // this is needed to remove '\0' from the end of _input
    typedef typename Concatenate<
            boost::mpl::vector_c<char>,
            _input
    >::type type;
};

#define AT(z, i, data) , i < sizeof(data) ? data[i] : '\0'
#define _S(s) StaticString<char BOOST_PP_REPEAT(16, AT, s) >::type

#include <iostream>
using namespace std;
using boost::mpl::c_str;
using boost::mpl::size;

int main()
{
    typedef _S("Hello ") Hello;
    cout << c_str<Hello>::value << endl;
    cout << size<Hello>::type::value << endl;

    typedef _S("World!") World;
    cout << c_str<World>::value << endl;
    cout << size<World>::type::value << endl;

    typedef Concatenate<Hello, World>::type concatenated;
    cout << c_str<concatenated>::value << endl;
    cout << size<concatenated>::type::value << endl;

    return 0;
}