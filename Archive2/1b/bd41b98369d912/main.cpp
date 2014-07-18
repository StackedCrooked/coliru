constexpr bool contains(const char *s, char c) {
    for (; *s; ++s) {
        if (*s == c) {
            return true;   
        }
    }
    
    return false;
}

int main() {
    static_assert(contains("abcdef", 'b'), "");   
    static_assert(!contains("abcdef", 'g'), "");   
}