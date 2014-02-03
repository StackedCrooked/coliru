template<class T = int> struct X;

template<class T>
struct X{};

int main() {
    X<> x;
}