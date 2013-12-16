//#define BOOST_SPIRIT_DEBUG

#include <iostream>
#include <vector>
#include <boost/spirit/include/karma.hpp>
#include <boost/container/vector.hpp>

int main()
{
    boost::variant<boost::container::vector<int>, std::string> tmp = "test";
    std::string use;
    namespace karma = boost::spirit::karma;
    //Your original code
    bool r = karma::generate(std::back_insert_iterator<std::string>(use), +karma::int_ |   *karma::char_, tmp);
    std::cout << "r=" << std::boolalpha << r << ", Use: \""<< use << '"' << std::endl;
    
    //Create rules to expose explicitly the attributes you want
    use.clear();
    karma::rule<std::back_insert_iterator<std::string>,boost::container::vector<int>()> ints_rule = karma::int_%',';
    karma::rule<std::back_insert_iterator<std::string>,std::string()> string_rule = *karma::char_;
    r = karma::generate(std::back_insert_iterator<std::string>(use), ints_rule | string_rule, tmp);
    std::cout << "r=" << std::boolalpha << r << ", Use: \""<< use << '"' << std::endl;
    
    //Same test using ints
    use.clear();
    boost::container::vector<int> tmp_vector;
    tmp_vector.push_back(1);
    tmp_vector.push_back(2);
    tmp=tmp_vector;
    r = karma::generate(std::back_insert_iterator<std::string>(use), ints_rule | string_rule, tmp);
    std::cout << "r=" << std::boolalpha << r << ", Use: \""<< use << '"' << std::endl;
    
    //An example in which the variant has the exact same attributes exposed by the alternative generator
    use.clear();
    boost::variant<std::vector<int>, std::vector<char> > tmp2;
    std::vector<char> string;
    string.push_back('t');
    string.push_back('e');
    string.push_back('s');
    string.push_back('t');
    tmp2=string;
    r = karma::generate(std::back_insert_iterator<std::string>(use), karma::int_%',' | *karma::char_,tmp2);
    std::cout << "r=" << std::boolalpha << r << ", Use: \""<< use << '"' << std::endl;
}