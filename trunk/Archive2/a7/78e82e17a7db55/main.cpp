#include <iostream>

struct ostr {
        std::ostream& s;

        template<class T>
        ostr& operator<<(const T& x) { s << x; return *this; }
};

struct xy {
        double x, y;
};

template<class Stream>
Stream& operator<<(Stream& s, const xy& x) {
        s << "[" << x.x << ", " << x.y << "]";
        return s;
}

int main() {
        ostr os{std::cout};
        xy x{4, 5};
        os << "Value is: " << x <<"\n";
}