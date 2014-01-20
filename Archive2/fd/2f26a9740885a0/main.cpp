#include <iostream>
#include <map>
namespace A {
    class B {
        private:
            typedef std::map<int, int> C;
            C a;
            friend std::ostream& operator<<(std::ostream& os, const C &c) {
                for (C::const_iterator p = c.begin(); p != c.end(); ++p)
                    os << (p->first) << "->" << (p->second) << " ";
                return os;
            }
        public:
            B() {
                a[13] = 10;
                std::cout << a << std::endl;
            }
        };
}
int main() {
    A::B c;
}