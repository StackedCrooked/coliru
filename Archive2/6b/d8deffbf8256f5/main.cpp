#ifndef b_h
#define b_h

class a;

class b {
    public:
        friend a::a(const a&);
    private:
};

#endif

#ifndef a_h
#define a_h

class a {
    public:
        a() {}
    private:
};

#endif


int main() {
    return 0;
}