#include <iostream>
#include <set>
#include <iterator>
#include <vector>
using namespace std;

vector<double> data = { 7.1, 6.4, 8, 5.5, 8 };

template<typename T1, typename T2, typename T3>
void mycopy_if(T1 from, T1 end, T2 to, T3 cond) {
    while (from != end) {
        auto tmp = *from++;
        if (cond(tmp))
            *to++ = tmp;
    }
}
//struct less_7 { bool operator()(double val) { return (val < 7); } };
int main() {
    double limit = 7.0;
    mycopy_if(data.begin(), data.end(), ostream_iterator<double>(cout, " "),
              [limit](double val) { return (val < limit); }
             );
}