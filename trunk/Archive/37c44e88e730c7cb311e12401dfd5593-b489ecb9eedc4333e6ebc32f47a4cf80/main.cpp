#include <vector>

// functions are undefined and thus unoptimizable
void disappear(int);
int* get_data();
int get_length();


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

template<typename It>
void process(It begin, It end)
{
    for (It it = begin; it != end; ++it)
    {
        disappear(*it);
    }
}


#else


// Use simple pointer
void process(int* begin, int* end)
{
    for (int* it = begin; it != end; ++it)
    {
        disappear(*it);        
    }
}


#endif


int main()
{
    int* a = get_data();
    int length = get_length();
    
#ifdef USE_ITERATOR
    process(Wrap(a), Wrap(a + length));
#else
    process(a, a + length);
#endif
}

