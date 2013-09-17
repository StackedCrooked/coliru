template <typename T>
class Obj;
 
template <typename T>
Obj<T> make_obj(T t);

template <typename T>
class Obj {
    private:
        T & t;
        Obj (T & t) : t(t) { }
        Obj() = delete;

template <typename T2>
friend Obj<T2> make_obj(T2 t);
};

template <typename T>
Obj<T> make_obj(T t) { 
    return Obj<T>(t);
}

int main()
{
    auto a = make_obj<int>(42);
    (void)a;
}
