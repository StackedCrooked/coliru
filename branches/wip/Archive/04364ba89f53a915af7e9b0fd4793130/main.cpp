int main()
{
    int b;
    void * bp = &b;
    new (bp) int;
}

