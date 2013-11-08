#include <iostream>

using std::cout;
using std::endl;

struct Int {
    const int& val;
};

Int test(){
    return Int {30};
}

int main()
{
    Int i = Int{30};

    cout << i.val << endl;

    Int j = test();

    cout << j.val << endl;

    return 0;
}