int main()
{
    typedef decltype(sizeof(0)) my_size_t;
    
    my_size_t x   = 0;  // OK
    std::size_t y = 1;  // error: 'size_t' is not a member of 'std'
}