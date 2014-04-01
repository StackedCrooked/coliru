#include <iostream>
#include <string>
#include <iterator>
#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

template <typename OutputIterator> struct grammar : karma::grammar<OutputIterator, std::nullptr_t()> {
    grammar() : grammar::base_type(query) {
        query = karma::eps << "yeah";
    }

    karma::rule<OutputIterator, std::nullptr_t()> query;
};


int main(void) {
    typedef std::back_insert_iterator<std::string> iterator_type;
    std::string generated;
    iterator_type output_it(generated);

    //keys_and_values<sink_type> g;
    grammar<iterator_type> g;
    bool result = karma::generate(output_it, g, nullptr);
    std::cout << std::boolalpha << result << ":" << generated << std::endl;
}
