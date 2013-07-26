struct S {
    S(int){}    
    
    void operator+(S){}
};

int main() {
    S s{5};
    s + 2;
}