#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class myvector : public vector<T>
{
    ostream& operator<<(ostream &os)
    {
        os << "haha" << endl;
        return os;
    }
};

template <typename T>
void show(T t)
{
    for(const auto &tt : t)
    {
        cout << tt << " ";
    }
    cout << endl;
}

int main()
{
    myvector<int> vec;
    vec.push_back(1);
    show(vec);
    auto t = find_if(begin(vec), end(vec), [](const int &t){return (t>=3 && t<=5)?true:false;} );
    cout<< *t << endl;
    
    auto i = count_if(begin(vec), end(vec), [](const int &t){return (t>=3 && t<=7)?true:false;} );
    cout << i << endl;
    
    cout << vec;
    
    return 0;
}
