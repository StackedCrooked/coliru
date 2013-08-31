
void mystery_write(int);
int mystery_read();


namespace {



bool check(int value)
{
    return (value % 2 != 0) && (value % 3 != 0) && (value % 5 != 0) && (value % 7 != 0);
}


void test()
{
    for (int i = 0; i != 1000; ++i)
    {
        mystery_write(check(mystery_read()));
    }
}
}

int main()
{
    test();
}