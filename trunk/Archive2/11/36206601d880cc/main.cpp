#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <functional>
#include <boost/algorithm/string/case_conv.hpp>
using namespace std;

int main()
{

vector<string> strings = {"Foo", "Bar"};
vector<string> lower_cased_strings;
transform(
    strings.begin(),
    strings.end(),
    inserter(lower_cased_strings, lower_cased_strings.end()),
//  Variant 1
//  [](const string &word) {
//      return boost::to_lower_copy(word);
//  }
//  Variant 2
//  [](const string &word) {
//      return boost::to_lower_copy<string>(word);
//  }
//  Variant 3
    std::bind(
        boost::to_lower_copy<string>,
        std::placeholders::_1,
        std::locale())
    );
}