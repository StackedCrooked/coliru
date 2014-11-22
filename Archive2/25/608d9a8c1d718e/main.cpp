#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Pool
{
    function<int()> generator;

    function<int()> next(vector<int> v, size_t i)
    {
        return [this, v=move(v), i]{
            auto tmp = v[i];
            auto size = v.size();
            generator = next(move(v), (i+1)%size);
            return tmp;
        };
    }
public:    
    Pool(vector<int> v)
    {
        generator = next(move(v), 0);
    }
    
    int operator()()
    {
        return generator();
    }
};

int main()
{
    Pool p { {1,2,3} };
    cout << p() << endl;
    cout << p() << endl;
    cout << p() << endl;
    cout << p() << endl;
}
