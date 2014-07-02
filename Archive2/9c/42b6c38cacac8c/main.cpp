void foo(int* p) {}
 
int main() {
    volatile int a;
    foo(&a);
    return 0;
}