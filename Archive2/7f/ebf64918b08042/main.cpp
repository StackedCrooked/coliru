struct A
{
private:
    int (*_foo)(int a, int b);

public:
    (*operator int() const)(int, int)
    {
        return _foo;
    }
};

int main(){ }
