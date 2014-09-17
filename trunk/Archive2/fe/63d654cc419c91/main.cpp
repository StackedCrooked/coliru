
struct X
{
    enum E { A, B, C };
    static constexpr int noElems() { return C+1; };
    static constexpr int N = noElems();
};

int main () { 

}