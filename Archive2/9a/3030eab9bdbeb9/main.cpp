template<class>
struct foo {
    struct bar {
        template<class> void quux(){}
    };
    void f(){
        bar b;
        b.quux<int>();
    }
};

int main(){
    foo<char>().f();
}