typedef int *Type;

void foo(const Type &t) {
    *t = 2; //oops   
}

int main() {
    int i;
    foo(&i);
}