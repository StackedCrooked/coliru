#include <vector>
#include <iostream>
using std::cout;
using std::endl;

void showFloatArray(const std::vector<float>& v) {
    for (float f : v) {
        cout << " " << f;
    }
    cout << endl;
}

int main()
{
    std::vector<float> v{1,2,3};
    showFloatArray(v);
}