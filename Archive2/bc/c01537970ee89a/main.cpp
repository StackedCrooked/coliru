bool b;

struct Proxy {
    operator bool & () const { return b; }
};

int main() {
    bool& ref = Proxy();
}