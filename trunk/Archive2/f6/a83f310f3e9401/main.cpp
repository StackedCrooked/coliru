struct B {
    virtual f();
}; 

struct D final_overrider : B 
{
    void f(); /* must override, we are the final overrider*/
}; 

struct J :  B
{
        
}
struct E : J, D {
    void f();
}; 
