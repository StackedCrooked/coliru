void foo(int){}
void foo(int &){}

int main() {
    foo(5);
    
    int i{};
    static_cast<void(*)(int &)>(foo)(i);
}