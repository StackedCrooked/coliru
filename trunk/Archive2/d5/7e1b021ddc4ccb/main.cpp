#include <cstdio>

class Outer
{
private:
    static bool m_bool;
public:
    struct Inner {
        void print() {
            printf("m_bool: %s", (Outer::m_bool) ? "true" : "false");
        };
    };
};

bool Outer::m_bool = true;

int main() {
    Outer::Inner obj;
    obj.print();
    return 0;
}