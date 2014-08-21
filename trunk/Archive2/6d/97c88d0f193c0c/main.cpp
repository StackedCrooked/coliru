namespace test 
{ 
    namespace detail 
    { 
    }
    
    inline namespace v1 
    { 
        namespace detail 
        { 
            void foo() 
            { 
            }
        }
    }
}

int main()
{ 
    test::detail::foo(); 
}
