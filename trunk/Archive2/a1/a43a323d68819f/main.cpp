struct C
{
    static int v[];
};

int main() 
{
    int (*p)[] = &C::v; // works in C++ if 'v' isn't defined (only declared)
    return 0;
}