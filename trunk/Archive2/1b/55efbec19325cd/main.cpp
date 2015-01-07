
struct Typeless
{
    void* obj;
    void (*destroy)(void*);
};

template<typename T>
Typeless make_concealed(const T& value)
{
    struct Helper
    {
        static void destroy(void* p)
        {
            delete static_cast<T*>(p);
        }
    };
    
    Typeless p;
    p.obj = new T(value);
    p.destroy = &Helper::destroy;
    return p;
}


int main()
{
    auto n = make_concealed(2);
    n.destroy(n.obj);
}
