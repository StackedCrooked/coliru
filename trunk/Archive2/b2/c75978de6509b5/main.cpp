#include <iostream>
class a;
class b
{
    public:
    b()=default;
    b(const a&){}
};

class a
{
    public:
    operator b()
    {
        return b();
    }
};
void fun(b ){}
int main()
{
a c;
fun(c);

}

