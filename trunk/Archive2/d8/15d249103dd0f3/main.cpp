#include <iostream>


class B { 
            public:
             B() = default; 
             
             virtual void test_is_a () const
             {
                 std::cout << " I AM NOT A" << std::endl;
                 //k =2;
             } 
             
             protected:
             int a; 
             const char *bptr {"INITIAL BASE CHAR POINTER"}; 
             
             const  B* get_it()
             {
                 return this;
             }
             
             private:
             int k;
             
};

class A : protected B { 
            public:
            A() = default; 
            B c; 
            int d; 
            const char *aptr 
            {"INITIAL DERIVED CHAR POINTER"};
            
            //void test_has_a ()
            //{
            //    std::cout << c.a;
            //}
            
            virtual void test_is_a ()
            {
                std::cout << B::a << std::endl;
                std::cout << B::bptr << std::endl;
            }
            
            void test_access()
            {
                    d = B::a;
            }
            
            const B * get_B()
            {
                return this;
            }
};

class C: public A {  public: C()=default; };


int main ()
{
    A a = A();
    
    const B * b = &a.c;
    
    //const B * b = a.get_B();
    
    b->test_is_a();
    a.test_is_a();
    
    b =  a.get_B();
    
    b->test_is_a();
    
    //C f = C();
    
    
    
    
    
        
    
    
}
    
    


    