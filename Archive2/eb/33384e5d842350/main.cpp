int foo()
{
   return 123; 
}

int main()
{
    auto pFunc = &foo;
    
    void *ps = static_cast<void*>( pFunc );
    
    void *pr = reinterpret_cast<void*>( pFunc );
    
    (void)ps;
    (void)pr;
}
