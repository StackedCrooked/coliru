#include <string>
using std::string;

struct MyFoo {
    int     v_;
    string  n_;
    bool operator(int v) const
    { return v_ < v;}
 };