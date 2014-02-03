struct S {
    int count;
    void operator++() {
        count++;
    }
};

int main() {
    S s;
    s++;
    ++s;
}