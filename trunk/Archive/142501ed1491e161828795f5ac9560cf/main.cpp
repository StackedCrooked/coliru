class B {};
class C : private B {};
int main() {
    C c;
    auto p3 = (B*)(&c);
    auto p = static_cast<B*>(&c);
    auto p2 = reinterpret_cast<B*>(&c);
}