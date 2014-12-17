#include <iostream>
#include <string>
#include <exception>
#include <boost/lexical_cast.hpp>
namespace boost
{
    template<typename T>
        typename std::enable_if<boost::is_integral<T>::value, T>::type 
            lexical_cast(const std::string &str)
        {
            std::cout << __PRETTY_FUNCTION__ << "\n";
            if(str.empty()) //handle preconditions here, some custom logic
                return T();

            T result;

            if (!conversion::try_lexical_convert(str, result))
                throw bad_lexical_cast();

            return result;
        }
}


#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main()
{
    try
    {
        //1.
        auto p1_ = lexical_cast<int>(std::string(""));
        std::cout << "p1 = " << p1_ << std::endl; //displays 0, which is correct. calls overloaded lexical_cast()

        //2.
        auto p2_ = lexical_cast<int>(std::string("1"));
        std::cout << "p2 = " << p2_ << std::endl; //displays 1, which is correct. calls overloaded lexical_cast()

        //3.
        std::locale locale_;
        boost::date_time::format_date_parser<boost::gregorian::date, char> parser_("", locale_);
        boost::date_time::special_values_parser<boost::gregorian::date, char> svp_;
        boost::gregorian::date date_ = parser_.parse_date("2014-Dec-17", "%Y-%b-%d", svp_);  //calls boost::lexical_cast(), but I want call to overloaded lexical_cast() instead.

        std::cout << date_ << "\n";
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
