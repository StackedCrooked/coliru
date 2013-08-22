class Exx;

class Ex {
public:
    Ex():_val(0){}
    Ex(int val):_val(val){}
    Ex(Ex const &e): _val(e._val) { }
    ~Ex() {}
    void test(Exx &exx);
    int _val;
};

class Exx {
public:
    Exx():_val(0){}
    Exx(int val):_val(val){}
    Exx(Exx const &e): _val(e._val) { }
    ~Exx() {}
    void test(Ex &e) { e.test(*this); }
    int _val;
};

void Ex::test(Exx &exx)
{
    exx._val = 10;
}

int main() {
    Exx exx;
    Ex ex;

    exx.test(ex); //compile error: "undefined reference to `Exx::test(Ex&)'"

    return 0;
}
