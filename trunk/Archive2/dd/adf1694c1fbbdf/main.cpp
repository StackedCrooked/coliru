struct S {
    friend void foo() {}  
};

int main() {
    foo();   
}