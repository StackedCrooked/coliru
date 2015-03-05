#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename It, typename V = long, typename Skipper = qi::blank_type>
struct verbiage : qi::grammar<It, Skipper> {
    verbiage() : verbiage::base_type(start) {
        using namespace qi;

        auto value_ = qi::create_parser<V>();
        
        start = eval;
        eval  = no_case [
                 as_string [ raw [ value_[_a=_1] >> ('+'    |  lit("plus"))               >> value_[_b=_1] ] ] [ std::cout << _1 << " is " << (_a+_b)     << "\n" ]
               | as_string [ raw [ value_[_a=_1] >> ('-'    |  lit("minus"))              >> value_[_b=_1] ] ] [ std::cout << _1 << " is " << (_a-_b)     << "\n" ]
               | as_string [ raw [ value_[_a=_1] >> ('/'    |  lit("divided") >> "by")    >> value_[_b=_1] ] ] [ std::cout << _1 << " is " << (_a/_b)     << "\n"]
               | as_string [ raw [ value_[_a=_1] >> ('*'    |  lit("multiplied") >> "by") >> value_[_b=_1] ] ] [ std::cout << _1 << " is " << (_a*_b)     << "\n" ]
               | as_string [ raw [ lit("min") >> "of" >> value_[_a=_1] >> "and" >> value_[_b=_1] ] ]           [ std::cout << _1 << " is " << min_(_a,_b) << "\n" ]
               | as_string [ raw [ lit("max") >> "of" >> value_[_a=_1] >> "and" >> value_[_b=_1] ] ]           [ std::cout << _1 << " is " << max_(_a,_b) << "\n" ]
              ]
              ;
    }
  private:
    struct min_f { 
        using result_type = V; 
        template <typename A, typename B> V operator()(A a, B b) const { return std::min(a,b); }
    };
    struct max_f { 
        using result_type = V; 
        template <typename A, typename B> V operator()(A a, B b) const { return std::max(a,b); }
    };

    phx::function<min_f> min_;
    phx::function<max_f> max_;
    qi::rule<It, Skipper, qi::locals<V,V> > eval;
    qi::rule<It, Skipper> start;
};

int main() {
    using It = boost::spirit::istream_iterator;
    It f(std::cin >> std::noskipws), l;

    bool ok = qi::phrase_parse(f, l, verbiage<It>() % qi::eol, qi::blank);

    std::cout << "Success: " << std::boolalpha << ok << "; Remaining: '" << std::string(f,l) << "'\n";
}
