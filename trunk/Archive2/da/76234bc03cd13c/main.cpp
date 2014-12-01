template <template <typename> class D>
class Bar 
{
public:
    Bar& operator=(const Bar&) { return *this; }
};

template <typename T>
class Foo : public Bar<Foo>
{
public:
    Foo& operator=(const Foo& other) 
    { 
        Bar<Foo>::operator=(other);
        return *this;
    }
};

int main()
{
    Foo<int> f, g;
    f = g;
}