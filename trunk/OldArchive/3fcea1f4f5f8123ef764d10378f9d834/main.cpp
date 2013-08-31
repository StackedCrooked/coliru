#include <iostream>
#include <vector>
using namespace std;

class class1
{

public:
    class1() : _cancel(false) { }

//private:
    bool _cancel;

};

class class2
{

public:
    class1 obj1;
};


class class3
{
public:

    void addClass2(class2 _obj2) {
        this->_obj2.push_back(_obj2);
    }
    
    std::vector<class2> _obj2;
};

int main()
{
    class2 object2;
    class3 object3;
    object3.addClass2(object2);
    
    cout << boolalpha << object3._obj2[0].obj1._cancel << endl;
}