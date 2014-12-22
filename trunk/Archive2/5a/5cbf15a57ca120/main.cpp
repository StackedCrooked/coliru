int main()
{
    int x = 0;
    int* __restrict__ ptr = &x;
    
    (void)ptr;
}
