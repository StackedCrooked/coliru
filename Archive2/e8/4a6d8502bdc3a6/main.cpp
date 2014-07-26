#include <iostream>

using namespace std;

template <typename T>
class Outer
{
private:
    struct Inner { };
};

template <typename T>
void testFunction (const typename Outer<T>::Inner* p)
{
    cout << "Hello!" << endl;
}

template<>
class Outer<double>{
public:
    struct Inner { };
};

int main()
{
    Outer<double>::Inner i;
    testFunction<double>(&i);
    return 0;
}
