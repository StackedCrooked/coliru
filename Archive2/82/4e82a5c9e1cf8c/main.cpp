class MyClass
{
public:
    int m_num;
    MyClass() { m_num = 1;}
    const MyClass& operator+(const MyClass& mcls)
    {
        MyClass temp;
//        temp = m_num + mcls.m_num;
        return temp;
    }
};