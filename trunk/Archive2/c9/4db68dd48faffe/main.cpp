struct A{
    A() : a((char*)malloc(10)) {}
    const char* get() const {
        return a;
    }
    private:
        char* a;
};

int main(){
    A a;
    free(a.get());
    
    return 0;
}
