struct S {
    S(int){}    
};

void operator+(S, S){}

int main() {
    S s{5};
    s + 2;
}