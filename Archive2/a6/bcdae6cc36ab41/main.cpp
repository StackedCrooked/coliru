class Y {
private:
    int z;
public:
    Y() { z = 1; }
    int& r() { return z; }
    const int& r() const { return z; }
};

class X {
public:
    Y x;
};

int main(int, char*[]) {
    const X y;
    y.x.r() = 3;
    return 0;
}