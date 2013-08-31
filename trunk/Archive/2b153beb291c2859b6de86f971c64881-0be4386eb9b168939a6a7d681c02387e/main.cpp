template<typename T, int N>
class A {
public:
    void func();
};

template<int N>
class A<int, N> {
public:
    void func();
};

template<int N>
void A<int, N>::func()
{
}

int main()
{
}