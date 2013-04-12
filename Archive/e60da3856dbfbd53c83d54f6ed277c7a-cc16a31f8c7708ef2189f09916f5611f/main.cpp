
// functions are undefined and thus unoptimizable
void disappear(int);
int* get_data();
int get_length();

int* a = get_data();
int length = get_length();

// Utility for ASM mark points.
template<int> void ____ASM__MARKER____();
#define ASM_MARKER() ____ASM__MARKER____< __COUNTER__ >()


#ifdef USE_ITERATOR


// Use wrapper
struct Wrap
{
    Wrap(int* data) : data_(data) {}
    
    Wrap& operator++()
    {
        ++data_;
        return *this;
    }
    
    const int& operator*() const { return *data_; }
    int& operator*() { return *data_; }
    
    friend bool operator!=(const Wrap& lhs, const Wrap& rhs)
    {
        return lhs.data_ != rhs.data_;
    }
    
    int* data_;
};

void process(Wrap begin, Wrap end)
{
    ASM_MARKER();
    for (Wrap it = begin; ASM_MARKER(), it != end; ASM_MARKER(), ++it)
    {
        ASM_MARKER();
        disappear(*it);
    }
    ASM_MARKER();
}


#else


// Use simple pointer
void process(int* begin, int* end)
{
    ASM_MARKER();
    for (int* it = begin; ASM_MARKER(), it != end; ASM_MARKER(), ++it)
    {
        ASM_MARKER();
        disappear(*it);        
    }
    ASM_MARKER();
}


#endif


int main()
{
    
#ifdef USE_ITERATOR
    process(Wrap(a), Wrap(a + length));
#else
    process(a, a + length);
#endif
}

