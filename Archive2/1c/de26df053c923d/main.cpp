    #include<stdio.h>
    
    long double func()
    {
        return 1.0 ;
    }
    
    int main()
    {
       
       printf("%zu %zu\n",sizeof(func()), sizeof(main()));
       return 0;
    }
