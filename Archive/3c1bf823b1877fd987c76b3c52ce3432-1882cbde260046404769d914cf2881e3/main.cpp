
struct bar {};
struct foo : bar {};

int main()
{
    foo f;
    foo g = f;
    f = g;
}