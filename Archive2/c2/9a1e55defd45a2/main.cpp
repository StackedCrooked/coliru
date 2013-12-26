

template<typename T>
struct ThreadLocal
{
    ThreadLocal() : t(Get())
    {
        if (!t)
        {
            t = new T;
        }
    }
    
    T& get()
    {
        return *t;
    }
    
    ~ThreadLocal()
    {
        delete t;
        t = nullptr; // unset the static instance
    }
    
private:    
    T*& Get() // return by ref
    {
        static __thread T* t = nullptr;
        return t;
    }
    
    T*& t; // store as ref
};




int main() {}
