int main()
{
    int* beg = new int[10];
    int* end = beg + 10;
   
    while (beg != end)
        delete beg++;
}