#include <iostream>

class Foo
{
    private:
        const int* const p_abstract_const;   
        //int my application this is a pointer to abstract object
    public:
        Foo(const int* const p_new_concrete_const)
        {
            p_abstract_const  = p_new_concrete_const;
        }

        void printX()
        {
            std::cout << *p_abstract_const << std::endl;
        }
};

int main()
{
    int concrete_nonconst = 666;
    Foo foo(&concrete_nonconst); // I want this NOT to compile
    // Done!
    foo.printX();
    // The following below will always be possible,
    // because you declared it as an `int` in the first place
    // if you don't want it modified, make a copy, make it const,
    // or hide construction of the integer value
    concrete_nonconst=999;          // so that this will NOT be possible
    foo.printX();

}