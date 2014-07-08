int x;

int main() {
    int(::x); //does not compile
    int(::x + 2); //compiles
}