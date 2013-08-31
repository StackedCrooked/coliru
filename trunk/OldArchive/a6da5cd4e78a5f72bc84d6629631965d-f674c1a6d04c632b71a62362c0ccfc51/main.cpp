#include <boost/algorithm/string.hpp>
 
int main()
{
    std::vector<std::string> strings;
    std::string test = "what ";
    boost::split( strings, test, boost::is_any_of( " " ), boost::algorithm::token_compress_on );
    std::cout << strings.size() << "\n";
    for (auto string : strings)
    {
        std::cout << " (" << string << ")\n";
    }
}