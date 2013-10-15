#include <iostream>

void trace(const wchar_t *s) {
    std::wcout << s << '\n';
}
    
class BoxedInt
{
private:
    int m_int;
public:
    BoxedInt():m_int(0)
    {
        trace(L"Constructed with nothing");
    }

    BoxedInt(int val):m_int(val)
    {
        trace(L"Constructed with int");
    }

    BoxedInt(BoxedInt& val)
    {
        trace(L"Constructed with reference");
        m_int = val.m_int;
    }

    operator int()
    {
        trace(L"Cast to int");
        return m_int;
    }
};

BoxedInt funky()
{
    BoxedInt TempInt = 1;
    return TempInt;
}

int main(int argc, char* argv[])
{
    trace(L"Start");
    BoxedInt test1 = 1;
    trace(L"Copying");
    BoxedInt test2 = test1;
    trace(L"Assigning from return value");
    BoxedInt test3 = funky();
    trace(L"Done");
    return 0;
}