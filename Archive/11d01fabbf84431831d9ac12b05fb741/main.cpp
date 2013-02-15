#include <memory>


// you have to deal with an old legacy class that uses 2-phase init
struct Legacy
{
    Legacy() {}
    ~Legacy() {}
    
    // legacy class requires init and fini
    void init() {} 
    void fini() {}
};


// it's not possible to modify the legacy source code
// how would you write a adapter that uses RAII to ensure the request behavior?

struct raii
{
    raii(Legacy * l) : ptr(l)
    {
        ptr->init();
    }
    
    ~raii()
    {
        ptr->fini();
    }
    
    std::shared_ptr<Legacy> ptr;
};

int main()
{
    raii p(new Legacy);
}