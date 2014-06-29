struct C
{
    static int v[];
};

//int C::v[] = {1};

int main() 
{
    int (*p)[] = &C::v; // works in C++ if 'v' isn't defined (only declared)
    //*p[0] = 1; // Wont compile
    
    int a[] = {1};
    int b[] = {1,2};

    //p = &a; // works in C but not in C++
    //p = &b; // works in C but not in C++
    
    return 0;
}