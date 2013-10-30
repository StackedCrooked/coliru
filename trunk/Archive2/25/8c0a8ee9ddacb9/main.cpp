#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

float sigmoid(float x){ return x/*...*/;}

int main()
{
    using namespace std;
    const int a_size = 5; // input
    const int c_size = 2; // output
    const int b_size = a_size * c_size; // multipliers

    std::vector<float> a(a_size);
    std::vector<float> b(b_size);
    std::vector<float> c(c_size);

    // fill a and b with data
    auto i = 0;
    generate(begin(c), end(c), [&i, &a, &b]
    {
        return sigmoid(inner_product
        (
            begin(a), end(a),
            begin(b) + distance(begin(a), end(a)) * i++, 0.f
        ));
    });
    // this nested loop
    /*for(int i = 0; i<c_size; i++) {
        c[i] = 0.0;
        for(int k = 0; k<a_size; k++) {
            c[i] += (a[k] * b[i*a_size+k]);
        }
        c[i] = sigmoid(c[i]);
    }*/
}