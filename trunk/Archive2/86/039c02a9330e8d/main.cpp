bool lock = true;


#include <map>
#include <iostream>
#include <stdio.h>
    
    
std::map<void*, const char*> map;


extern "C"
{
    
    void __cyg_profile_func_enter(void*, void* call_site) __attribute__((no_instrument_function));
    void __cyg_profile_func_exit(void*, void* call_site) __attribute__((no_instrument_function));
}


int B() { }
int A() { B(); }


int main(int argc, char** argv)
{
    // map function pointer to name
    map[(void*)&A] = "A";
    map[(void*)&B] = "B";
    

    lock = false;
    A();
    lock = true;
}


void __cyg_profile_func_enter(void* this_fn, void* call_site)
{
    if (lock) return; lock = true;
    std::cout << map[this_fn];
    lock = false;
}


void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    if (lock) return; lock = true;
    std::cout << map[this_fn];
    lock = false;
}
