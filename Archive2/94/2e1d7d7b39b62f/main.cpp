struct foo 
{
    int i, j, k;
};

struct bar
{
    int i, j, k = 0;
};

int main()
{
    auto f = foo{ 1, 2, 3 };
    auto b = bar{ 1, 2 };
}
