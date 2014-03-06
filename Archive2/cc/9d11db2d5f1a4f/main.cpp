    #include <stdio.h>
    
    constexpr int f()
    {
        return printf("a side effect!\n");
    }
    
    int main()
    {
        char a[f()];
        printf("%zd\n", sizeof a);
    }