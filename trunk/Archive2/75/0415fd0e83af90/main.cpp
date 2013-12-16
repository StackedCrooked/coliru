

// QUIZ: Can you predict which statements will be accepted
//        and which will be rejected by the compiler?



template<typename T>
void test(T&) { }


int main()
{
    // 1. passing a non-const variable
    int a = 1;
    test(a);
    
    // 2. passing a const variable
    const int b = 2;
    test(b);
    
    // 3. passing a literal value
    test(3);
}
