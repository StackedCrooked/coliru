struct s
{
    typedef int val_type;
};

int main()
{
    s x;
    decltype(x)::val_type y;
}