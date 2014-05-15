struct S {
    friend void foo(S) {}  
};

int main() {
    foo(S());   
}