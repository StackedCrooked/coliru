
int main()
{
    bool test1 = true;
    bool test2 = true;
    if (! test1)
        if (test2)
            return 0;
        else
            return 1;
            
    return 2;
}
