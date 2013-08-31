template <typename F, typename... Args>
void apply(F f, Args... args) {
       // doesn't do much yet
}

bool f1(char c) {
    return c == 'c';
}

int main() {
    apply(f1, 'c');
}