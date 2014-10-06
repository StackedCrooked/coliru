#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
   const std::string a = "21,22,23,24";
   std::vector<std::string> words;
   boost::split(words, a, boost::is_any_of(","), boost::token_compress_on);
   std::vector<int> numbers;
   std::transform(words.begin(), words.end(), std::back_inserter(numbers), &boost::lexical_cast<int, std::string>);
   std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, "\n"));
}