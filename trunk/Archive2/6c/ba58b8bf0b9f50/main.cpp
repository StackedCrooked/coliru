
struct X
{
    static constexpr int noElems() { return 1; };
    static constexpr int N = noElems();
};

int main () { 
}