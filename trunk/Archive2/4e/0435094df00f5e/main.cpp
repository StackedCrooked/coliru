#include <valarray>
#include <vector>

int main() {
    using namespace std;
    vector<int> v{2,0,1,0,0,1,1,0,0,0}; // Any vector
    valarray<int> va(std::begin(v), std::end(v));
}