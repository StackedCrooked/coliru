#include <stdio.h>
#include <utility>

struct Obj {
    int Id;
    Obj(int id) : Id(id) { printf("Constructor of %d\n", Id); }
    Obj(Obj&& obj) : Id(obj.Id) { printf("Constructor from lvalue reference of %d\n", Id); obj.Id = -1; }
    ~Obj() { printf("Destructor of %d\n", Id); }
private:
    Obj(const Obj&);
    const Obj& operator= (const Obj&);
};

Obj f() {
    Obj result(1);
    return result;
}

int main() {
    Obj a = f();
    return 0;
}