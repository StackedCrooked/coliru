template<typename T>
struct id { typedef T type; };

template<typename ...T>
void f(void(*)(T...));

void g();
void g(int);

int main() {
    f(g);
}