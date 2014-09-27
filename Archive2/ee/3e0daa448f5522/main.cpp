struct S {
    int operator=(const S &) {
        return 5;
    }
};

int main() {
    int a;
    S b;
    S c;
    
    //compiles
    a = b = c; 
    
    //doesn't compile
    b = c;
    a = b;
}