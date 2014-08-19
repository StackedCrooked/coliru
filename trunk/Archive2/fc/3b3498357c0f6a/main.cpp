struct String {
    char str[10]{};
    
    constexpr String(const char *s) {
        int i = 0;
        do {
            str[i] = s[i];
        } while (s[i++]);
    }
};

int main() {
    constexpr String s{"abc"};
}

