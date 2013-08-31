template<typename T> struct foo;

template<typename T>
void touch(foo<T>& f)
{
    ++f.privates;
}

template<typename T>
struct foo {
private:
    T privates = 0;
    
    friend void touch<>(foo& f);
};

int main()
{
    foo<int> f;
    touch(f);
}