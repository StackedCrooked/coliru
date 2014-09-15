#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <boost/phoenix/operator.hpp>


using namespace std;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

struct myfunc
{
    template<class T>
    struct result { typedef void type; };

    void operator()(const vector<int> & data, int N) const
    {
            copy( data.begin(), data.end(), ostream_iterator<int>(cout,"\n"));
            cout << "Total Number of Elements = " << N << endl;
    }
};

int main() {
    string hello = "10, 20";
    string::const_iterator first = hello.begin(), last = hello.end();
    
    qi::rule< string::const_iterator, ascii::space_type, qi::locals<int> > myrule = 
        (qi::int_[qi::_a++] % ',')[ phoenix::bind(myfunc(), qi::_1, qi::_a) ];

    bool res = qi::phrase_parse( first, last, myrule, ascii::space);
    
    cout << boolalpha << res << ", " << boolalpha << (first == last) << endl;
    
    return 0;

}
