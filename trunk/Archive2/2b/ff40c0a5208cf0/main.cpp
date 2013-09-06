#include <vector>

using namespace std;

struct T {
    vector<double>& v;
    T(vector<double>& vv) : v{vv} {}
};

int main()
{
}
