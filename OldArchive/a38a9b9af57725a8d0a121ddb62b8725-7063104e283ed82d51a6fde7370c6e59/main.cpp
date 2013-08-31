int main() {
    union {
        float f;
        int i;
    } u;

    u.f = 1.01f;
    return u.i;
}