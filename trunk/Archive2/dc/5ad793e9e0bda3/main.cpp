#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> square_vec(const vector<int>& v)
{
    vector<int> result;
    result.reserve(v.size());
    back_insert_iterator< std::vector<int>> back_it (result);
    transform(v.begin(), v.end(), back_it, [](int i)  
            {   
                return i*i;
            }); 
    return result;
}

int main() {
    vector<int> my_vec = {1 ,2,3,4,5,6,7,8,9,10};
    vector<int> result_vec;
    result_vec = square_vec(my_vec);
    cout << "OK";
    return 0;
}