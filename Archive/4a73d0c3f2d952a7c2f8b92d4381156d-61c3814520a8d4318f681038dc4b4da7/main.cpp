struct a {
    int x;
};

struct b {
    int x, y;  
};

void foo(a) {}
void foo(b) {}

int main() {
    foo({1});
}