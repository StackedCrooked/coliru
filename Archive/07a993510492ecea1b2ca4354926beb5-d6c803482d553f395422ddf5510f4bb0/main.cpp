class foo {};
int& operator||(foo, foo) {
    static int x = 0;
    return x;
}

int main() {
    foo localvar1, localvar2;
    localvar1 || localvar2 = 5;
}