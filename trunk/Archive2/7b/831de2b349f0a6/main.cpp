#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

template<typename Func>
void find_min_value(const vector<int>& v, Func call_on_result)
{
    auto min_value = *min_element(begin(v), end(v));
    call_on_result(min_value);
}

int main()
{
    vector<int> v1 = {30, 15, 60};
    vector<int> v2 = {17, 18, 19, 20};
    vector<int> v3 = {25, 23, 16};
    find_min_value(v1, [&](int min_v1){
        find_min_value(v2, [&](int min_v2){
            find_min_value(v3, [&](int min_v3){
                cout << min(min_v1, min(min_v2, min_v3)) << '\n';
            });
        });
    });
}
