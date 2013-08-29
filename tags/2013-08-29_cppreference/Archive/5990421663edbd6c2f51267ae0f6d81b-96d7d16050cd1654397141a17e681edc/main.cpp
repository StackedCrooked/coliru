
struct foo { ~foo() {} };

int main()
{
    foo f;
    foo g = f;
}