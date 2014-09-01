#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/variant.hpp>

#define P_(x) \
    std::cout << __FUNCTION__ << ':' << __LINE__ << "  " \
              << #x << " == " << (x) << std::endl

struct process : boost::static_visitor<> {
    template<typename T> void operator()(const T &v) const {
        P_(v);
    }
} ;

int main() {
    using namespace std;
    using str_or_dbl = boost::variant<string, double>;
    vector<str_or_dbl> v;
    string w;
    while (cin >> w) {
        char *p;
        const auto dval = strtod(w.c_str(), &p);
        str_or_dbl tmp;
        if (*p != 0)
            tmp = w; // kein double
        else
            tmp = dval; // war double
        v.push_back(tmp);
    }
    
    for (auto &e : v) {
        boost::apply_visitor(process(), e);
/*
        if (auto *p = boost::get<double>(&e)) {
            cout << *p << endl;
        }
        if (auto *p = boost::get<string>(&e)) {
            cout << *p << endl;
        }
*/
    }
}
