template <class T> int bit_sizeof(T unused) {
    long long a,b,c;
    T x;
    x^=x;
    x|=1;
    a=b=c=x;
    b<<=8;
    c<<=3;
    x=b;
    while (x) {
        a<<=1;
        b<<=c;
        c<<=1;
        x=b;
    }
    return a;
}

int main() {
    int* c = nullptr;
    return bit_sizeof(c);
}
