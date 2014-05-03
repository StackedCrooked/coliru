#include <tuple>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

int main() {
    using namespace std;
    using namespace boost::fusion;

    string result;
    for_each(make_tuple(1, 'a', 2.2), [&result](auto &s) {
        result += boost::lexical_cast<string>(s) + ' ';
    });

    cout << result << endl;
}