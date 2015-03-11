enum { i = 1 };
class X {
    char v[i]; // error: i refers to ::i
    // but when reevaluated is X::i
    enum { i = 2 };
};