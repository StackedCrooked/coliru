template<typename T>
void f(T t) { }

void f(double t) = delete;

int main() {
    f(10);
    f(1.0);
}