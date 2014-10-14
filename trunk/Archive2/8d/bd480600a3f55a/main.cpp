class Base1{
public:
    Base1(){}
    virtual ~Base1(){}
};

class D1:public Base1{

};

class D2:public Base1{

};

class Base2{
public:
    Base2(){}
    virtual ~Base2(){}
    virtual Base1 * fun() = 0;
};

class _D1:Base2{
public:
    D1* fun(){}
};

class _D2:Base2{
public:
    D2* fun(){}
};

int main()
{
}