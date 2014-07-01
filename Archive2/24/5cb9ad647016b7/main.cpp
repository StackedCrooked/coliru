template<typename T>
class X
{
public:
    X<T>() {}
    ~X<T>() {}
    X<T>& operator=(const X<T>& rhs) {}
};

int main()
{
    X<int> x;
}
