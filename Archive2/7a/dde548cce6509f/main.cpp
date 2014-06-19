int f(int x, int y = 10) { return x * y; }

template<typename T>
using alias = T;

int main() {
    alias<int(int, int)>* g = f;
    alias<int(int)>* h = f; // error
}