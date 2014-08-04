struct X {
    operator double();
};
struct Y {
    operator int*();
};
int *a = Y() + 100.0; // error: pointer arithmetic requires integral operand
int *b = Y() + X(); // error: pointer arithmetic requires integral operand

int main() { }