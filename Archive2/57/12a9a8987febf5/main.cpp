

template<typename CRT>
struct Item
{
    void foo()
    {
        static_cast<CRT&>(*this).foo_impl();
    }
    
    // must be implemented by subtype
    void foo_impl() = delete;
};
