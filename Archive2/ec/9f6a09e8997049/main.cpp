#include <stdio.h>
#include <utility>

struct Obj {
    int Id;
    Obj(int id) : Id(id) { printf("Constructor of %d\n", Id); }
    Obj(const Obj&& obj) : Id(obj.Id) { printf("Constructor from lvalue of %d\n", Id); }
    ~Obj() { printf("Destructor of %d\n", Id); }
private:
    Obj(const Obj&);
    const Obj& operator= (const Obj&);
};

Obj&& f() {
    Obj result(1);
    return std::move(result);
}

int main() {
    Obj a = f();
    return 0;
}