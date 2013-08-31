void f(double) = delete;
void f(int) {}

int main() {
    f(1.0);
}