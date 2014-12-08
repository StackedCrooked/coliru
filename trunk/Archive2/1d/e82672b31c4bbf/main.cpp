void foo(long long) { }
void foo(unsigned long long) { }
void foo(long double) { }

int main()
{
    int i = 0;
    foo(i);
}
