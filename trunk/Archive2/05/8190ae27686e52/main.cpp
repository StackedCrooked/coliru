int a; int a;

struct foo {
    int a[5];
};

struct bar {
    struct foo x, y;
};

int main(void)
{
    a = (struct bar) { .y.a[3] = 5 }.x.a[2];
}