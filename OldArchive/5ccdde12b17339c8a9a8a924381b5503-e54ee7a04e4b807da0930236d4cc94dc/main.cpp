void do_something(const char*) { }

int main()
{
    for (int i=0; i<10; ++i)
    {
        const char a[2] = { '0'+i };
        do_something(a);
    }
}