inline unsigned &sNextID()
{
    static unsigned data = 0;
    return data;
}

template<typename tag>
struct Foo
{
    static unsigned sNextID;
};

template<typename tag>
unsigned Foo<tag>::sNextID=0;

int main()
{
    sNextID() = 11;
    Foo<int>::sNextID = 22;
}