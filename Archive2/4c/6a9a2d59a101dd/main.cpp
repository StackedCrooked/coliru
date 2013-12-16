#include <bitset>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/timer.hpp>

using namespace std;
size_t const N = 10000000;

typedef string::const_iterator iter;
typedef boost::iterator_range<iter> string_view;

template<typename C>
void test_custom(string const& s, char const* d, C& ret)
{
    C output;

    bitset<255> delims;
    while (*d)
    {
        unsigned char code = *d++;
        delims[code] = true;
    }
    typedef string::const_iterator iter;
    iter beg;
    bool in_token = false;

    bool go = false;

    for (string::const_iterator it = s.begin(), end = s.end(); it != end; ++it)
    {
        if (delims[*it])
        {
            if (in_token)
            {

                output.push_back(typename C::value_type(beg, it));
                in_token = false;
            }
        }
        else if (!in_token)
        {
            beg = it;
            in_token = true;
        }
        else
        {
            if (!go)
            {
                cout << typename C::value_type(beg, it);
                //outputs the first character
                go = true;
            }
        }
    }

    if (in_token)
        output.push_back(typename C::value_type(beg, s.end()));
    output.swap(ret);
}

vector<string_view> split_string(string in, const char* delim = " ")
{
    vector<string_view> vsv;
    test_custom(in, delim, vsv);

    return vsv;
}

int main()
{
    string text = "123 456";

    vector<string_view> vsv = split_string(text);

    for (unsigned int i = 0; i < vsv.size(); i++)
        cout << endl << vsv.at(i) << "|" << endl;

    return 0;
}