#include <iostream>
#include <iterator>
#include <vector>

#include "boost/spirit/include/karma.hpp"

namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;
typedef std::back_insert_iterator<std::string> BackInsertIt;

int main( int argc, char* argv[] )
{
    std::vector<float> input;
    input.push_back(1.0f);
    input.push_back(2.0f);

    struct TestGram 
        : karma::grammar<BackInsertIt, std::vector<float>(), karma::space_type>
    {
        TestGram() : TestGram::base_type(output)
        {
            using namespace karma;
            floatRule = double_ | "0.0";

            output = -floatRule << -floatRule << -floatRule;
        }

        karma::rule<BackInsertIt, std::vector<float>(), karma::space_type> output;
        karma::rule<BackInsertIt, boost::optional<float>(), karma::space_type> floatRule;
    } testGram;


    std::string output;
    BackInsertIt sink(output);
    if (karma::generate_delimited(sink, testGram, karma::space, input))
        std::cout << "Generated: " << output << std::endl;
}
