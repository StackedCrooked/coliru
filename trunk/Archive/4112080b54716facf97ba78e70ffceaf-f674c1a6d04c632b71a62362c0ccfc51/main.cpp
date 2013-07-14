class Fuck;

template<typename T = Fuck>
T make_fucks(int b) {
    return T(b);
}
// This doesn't work though
// Fuck make_fucks(int b) {
//     return Fuck(b);
// }

struct Fuck {
    int a;
    Fuck(int a): a(a) {}
};

int main() {
    auto i = make_fucks(10);
}