
template<typename T, bool should_delete>
struct maybe_delete
{
    maybe_delete(T* t) : t(t) {}
    ~maybe_delete() { delete t; }
    T* t;
};

template<typename T>
struct maybe_delete<T, false>
{
    maybe_delete(T* t) : t(t) {}
    T* t;
};

