struct S;

struct S2 {
    static S s;  
};

struct S {};

S S2::s;

int main() {}