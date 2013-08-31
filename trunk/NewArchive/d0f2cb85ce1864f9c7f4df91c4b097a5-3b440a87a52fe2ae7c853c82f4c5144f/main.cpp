template<typename T>
void call(T *, void (T::*)()){}

struct S {
    void foo(){}
    
    void bar() const {
        call(this, &S::foo);
    }
};

int main() {}