template <int* P>
int* f() { return P; }

int main () {
    return static_cast<bool>(f<(int*)nullptr>());
}