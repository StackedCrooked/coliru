
template<class T, class...Us>
void func(T, Us...,T) {}

int main() {
    func(3, 4, 5);
}