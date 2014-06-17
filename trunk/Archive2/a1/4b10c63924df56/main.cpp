#include <vector>
#include <algorithm>
#include <iostream>
 
using namespace std;
class ABC
{
    public:
    void f2(int x)
    {
        cout<<x<<endl;
    }
};
 
int main3_15()
{
    ABC obj;
    function<void(int)> f1 = bind(&ABC::f2, obj, std::placeholders::_1);
    f1(20);
    
    return 0;
}

int main3_16()
{
    vector<int> v{1,2,3,4,5,6};
    for_each(v.begin(), v.end(), [](int val){cout<<val*2<<endl;});
    return 0;
}

void VendorJob(std::function<int(int)> val)
{
    cout<<"Red Apple"<<endl;
    int m = val(2);
    cout<<"Green Apple"<<m<<endl;
}

int main3_19()
{
    int local = 909;
    VendorJob([=](int x){cout<<"local="<<local<<endl; return x*401;});
    
    return 0;
}

template<typename T>
void VendorJobEx(std::function<T()>val)
{
    cout<<"Red Apple"<<endl;
    T m = val();
    cout<<"Green Apple"<<m<<endl;
}

int main3_20()
{
     int local = 909;
    VendorJobEx<int>([=](){cout<<"local="<<local<<endl; return 401;});
    return 0;
}

//template<typename T>
void DoJob(std::function<int()>val)
{
    cout<<"Red Apple"<<endl;
    int m = val();
    cout<<"Green Apple"<<m<<endl;
}

int main3_21()
{
    int local = 100;
    DoJob([=]()->int{cout<<"local="<<local<<endl; return 401;});
    return 0;
}

template<typename T1, typename T2>
void DoJobEx(T1 val)
{
    cout<<"Red Apple"<<endl;
    T2 m = val();
    cout<<"Green Apple"<<m<<endl;
}

int main3_22()
{
    int local = 100;
    DoJobEx<std::function<int()>, int>([=](){cout<<"local="<<local<<endl; return 404;});
    return 0;
}

std::function<void()> funretFun()
{
    int y= 10;
    int z = 100;
    return [&](){cout<< "Some return Val"<<y<<z<<endl;};
}

int main()
{
    std::function<void()> pt = funretFun();
    pt();
    return 0;
}