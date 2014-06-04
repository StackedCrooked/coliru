
int deadlock1();
int deadlock2();

int deadlock1()
{
    static int x = deadlock2();
    return x;
}

int deadlock2()
{
    static int x = deadlock1();
    return x;
}


int main()
{
    return deadlock1();
}
