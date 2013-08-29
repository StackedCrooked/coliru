struct S {
    S(int){}    
    
    void operator+(int){}
};

int main() {
    S s{5};
    s + 2;
}