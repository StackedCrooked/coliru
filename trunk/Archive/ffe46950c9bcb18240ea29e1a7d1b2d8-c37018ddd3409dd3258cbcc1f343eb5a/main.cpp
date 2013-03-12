void foo(const char *);

int main()
{
    for (int i = 0; i != 10; ++i)
    {
        foo("The quick brown fox jumps over the lazy dog.");
    }
}