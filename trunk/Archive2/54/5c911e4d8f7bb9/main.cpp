int main()
{
    int a = 0;
    
    #define a b
    #define b a

    a = 5;
}