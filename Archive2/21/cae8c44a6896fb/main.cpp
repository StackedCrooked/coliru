#include <string>
#include <vector>

using namespace std;

typedef vector<string> Strings;

void print(string const& s) {
    printf(s.c_str());
    printf("\n");
}

void print(Strings const& ss, int i) {
    print("Test " + to_string(i));
    print("Number of strings: " + to_string(ss.size()));
    for (auto& s: ss) {
        auto t = "length = " + to_string(s.size()) + ": " + s;
        print(t);
    }
    print("\n");
}

void test() {
    Strings a{"hello"};
    print(a, 1);

    Strings b{{"hello", "there"}};
    print(b, 2);

    Strings c{"hello", "there", "kids"};
    print(c, 3);
}

int main() {
    Strings b{{"hello", "there"}};
    print(b, 1);
}