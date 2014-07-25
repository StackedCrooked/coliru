struct S {
    int &r;
    
    S() {
        int &r = 5;
    }
};

int main() {
    S s;   
}