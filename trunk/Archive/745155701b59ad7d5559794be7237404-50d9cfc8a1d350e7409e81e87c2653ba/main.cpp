template <typename T>
void f(T& x) { x++; }
 
int main() {
    int i = 0;
    f<int const>(i);
}