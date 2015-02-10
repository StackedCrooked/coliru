template<typename T>
struct X
{
};

struct Y : X<int>
{
};

template<typename T>
void foo(X<T>) { }

int main()
{
    Y y;
    foo(y);
}