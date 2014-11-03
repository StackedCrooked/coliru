struct X
{
    template <class T>
    friend void f(T t);
};

template <class T>
void f(T t = T()) {}

int main()
{
    
}