void foo(int* p);

void foo(int p[42])
{
}

int main()
{
    int arr[42];
    foo(arr);
    
    int hmm[100];
    foo(hmm);     // dela
    
    int i;
    foo(&i);     // to tud
}