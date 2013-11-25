namespace lounge {
    constexpr int strlen(char const* c) {
        return *c? 1 + strlen(c+1) : 0;
    }
}

int test[lounge::strlen("foo")];

int main () {}
