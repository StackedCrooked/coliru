
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