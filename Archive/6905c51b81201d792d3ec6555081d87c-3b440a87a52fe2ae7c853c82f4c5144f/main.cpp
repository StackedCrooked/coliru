void foo(int **p){}

int main() {
    int n[20];
    foo(&n);
}