int main()
{
    // error: invalid conversion from 'int' to 'void*'
    ::operator delete(new int, 1); 
}