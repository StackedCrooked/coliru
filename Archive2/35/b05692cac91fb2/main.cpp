template<typename T>
struct A{
    A(T **);
};

template<typename T>
A<T>::A(T *p_proc[]) {}

int main() {}