#include <iostream>
#include <vector>

struct MyStructType
{
    std::vector<int> my_vec;
};

class Foo
{
public:
    Foo() {}
    ~Foo() {}

    void MyFunc(int a)
    {
        m_struct.my_vec.push_back(a);
    }

public:
    MyStructType m_struct;
};

int main()
{
    Foo f;
    f.m_struct.my_vec.push_back(10);
}