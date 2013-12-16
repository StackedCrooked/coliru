//
// QUIZ: Can you predict which samples will be accepted
//        and which will be rejected by the compiler?


template<typename T>
void test(T&) { }

int main()
{   
    // 1
    int a = 68;
    test(a); 
    
    
    // 2
    const int b = 200;
    test(b); 

    const int &b2 = b;
    test(b2);

    // 3
//    test(42);
}
