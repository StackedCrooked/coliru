struct foo
{
    int m;
};

struct bar
{
    foo m0;
    decltype(m0.m) m1;
};

int main() {}