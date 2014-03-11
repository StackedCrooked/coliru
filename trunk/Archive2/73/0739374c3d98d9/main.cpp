#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

template<class T, class U>
T& operator<<(T& os, vector<U> vec)
{
    vector<string>::iterator begin = vec.begin();
    vector<string>::iterator end = vec.end();
    for (; begin != end; ++begin)
        os << *begin << " ";
    return os;
}

int main()
{
    vector<string> things({
        "car", "truck", "rabbit"
    });

    ostringstream oss;
    oss << things << endl;
    string str = oss.str();
    copy(str.begin(), str.end(), ostream_iterator<char>(cout, ""));
}
