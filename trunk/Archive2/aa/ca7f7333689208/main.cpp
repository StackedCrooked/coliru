void func_ptr(int*) {}
void func_ref(int&) {}

int main() {
    int a;
    int* b = &a;
    int** c = &b;
    int*** d = &c;
    
    func_ptr(b);
    func_ptr(*c);
    func_ptr(**d);
    
    func_ref(*b);
    func_ref(**c);
    func_ref(***d);
}