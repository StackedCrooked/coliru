class A {
    void operator=(A&&) && = delete; // no op= for rvalues
};

int main() {
 A() = A(); // error
 return 0; 
}