struct A{
    A() : a(new char) {}
    const char* get() const {
        return a;
    }
    private:
        char* a;
};

int main(){
    A a;
    delete a.get();
    
    return 0;
}
