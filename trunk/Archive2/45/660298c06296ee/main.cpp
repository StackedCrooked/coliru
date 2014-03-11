struct data {
    int a;
    struct {
        int b;
        int c;
    };
};

int main()
{
    struct data d;

    d.a = 0;
    d.b = 1;
    d.c = 2;
    return 0;
}