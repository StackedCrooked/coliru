#include <future>
#include <iostream>

using namespace std; // !!!


class cabc{
public:
    void pr()
    {
        cout<<"abcdef";
    }
};
int main()
{

    cabc cap;
    auto f = async(cap.pr);
    f.get();
    return 0;
}