#include <vector>
#include <algorithm>

struct X {};

bool operator<(int, X) { return true; }
bool operator<(X, int) { return true; }

int main(){
    std::vector<X> v;
    std::binary_search(v.begin(), v.end(), 0);
}
