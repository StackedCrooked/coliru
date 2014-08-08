int never_called_function();

int test_function(int* p)
{
    int x = *p; 
    if (!p) return never_called_function(); // dead code, shall be eliminated
    return x;
}