#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

int main()
{
    set<string> words;

    istringstream text(
        "If there's one good thing that's come out of the European debt crisis \n"
        "it's that the U.S. has been able to shield itself from much of \n"
        "the mess. The sentiment will continue in 2012 as the U.S.  \n"
        "economy is expected to grow faster than its European counterparts. \n"
        "That's according to the Organization for Economic Cooperation and \n"
        "Development which says the U.S. economy will expand at a 2.9% \n"
        "annual rate in the first quarter and then a 2.8% rate in the second quarter.");

    cout << text.str() << endl;

    std::copy(istream_iterator<std::string>(text), {}, inserter(words, words.end()));

    for (auto& e : words)
        cout << e << endl;
}
