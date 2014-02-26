struct S {
    int *p;  
};

int main() {
    S *s;
    s->*p;
}
