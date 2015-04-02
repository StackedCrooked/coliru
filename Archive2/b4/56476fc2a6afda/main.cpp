

struct Task
{
    using FPtr = void (*) (void*);    
    
    Task(FPtr fptr, void* storage) : fptr_(fptr), (storage) { }
    
    void operator()() { fptr_(storage_); }
    
    FPtr fptr_;
    void* storage_;
};