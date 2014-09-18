#include <iostream>
#include <vector>
using namespace std;

vector<int> usual_generate_array(int n)
{
    vector<int> result;
    for (int i = 1; i <= n; ++i)
        result.push_back(i);
    return result;
}

template<typename Func>
void new_generate_array(int n, Func call_on_result)
{
    vector<int> result;
    for (int i = 1; i <= n; ++i)
        result.push_back(i);
    
    call_on_result(result); // !!! Difference
}

void print_array(const vector<int>& arr)
{
    for (auto& elem : arr)
        cout << elem << ' ';
    cout << '\n';
}

int main()
{
    // Usual code
    auto arr = usual_generate_array(10);
    print_array(arr);
    
    // New style
    new_generate_array(8, print_array);
}
