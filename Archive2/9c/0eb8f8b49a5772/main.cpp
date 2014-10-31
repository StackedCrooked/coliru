struct X
{
private:
    void foo();
};

struct Y : X
{
    void bar()
    {
        foo();
    }
};

int main()
{
    Y y;
    y.bar();
}