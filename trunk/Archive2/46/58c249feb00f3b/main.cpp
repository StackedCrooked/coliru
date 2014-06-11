namespace N {

    class C {
    public:
        friend bool operator==(const C& c, const C& x) {
            return true;
        }
        friend bool f(const C& c, const C& x) {
            return true;
        }
    };

    class D {
    public:
        bool operator==(const D& x) {
            bool a = operator==(C{}, C{});
            return true;
        }
        bool f(const D& x) {
            bool a = f(C{}, C{});
            return true;
        }
    };
}

int main() {}