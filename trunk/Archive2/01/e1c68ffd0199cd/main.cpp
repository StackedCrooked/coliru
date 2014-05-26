
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using  std::cout;
using  std::endl;
using std::string;

int main()
{
    string strToSplit = "splitting strings, in|multiple ways";
    std::vector<std::string> words;
    boost::split(words, strToSplit, boost::is_any_of("\t ,|"));
    std::copy (words.begin(), words.end(), std::ostream_iterator<string>(cout, "\n"));

    words.clear();
    std::istringstream iss(strToSplit);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(words));
    std::copy (words.begin(), words.end(), std::ostream_iterator<string>(cout, "\n"));
    return 0;
}
