    #include <stdio.h>
    
    constexpr int f()
    {
        return printf("a side effect!\n");
    }
    
    int main()
    {
        constexpr int size = f();
        char a[size];
        printf("%zd\n", sizeof a);
    }