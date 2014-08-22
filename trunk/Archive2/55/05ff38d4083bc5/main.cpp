#include <iostream>

struct Base {
    int id;
    Base(int idIn = 0) : id(idIn) { }
};

struct Object : Base{
    int data;
    Object(int idIn = 0, int dataIn = 1) : Base(idIn), data(dataIn) { }
};

int main(int, char*[])
{
    Object o;
    Object *p = &o;
    Base *bo = &o;
    Base *bp = p;
    void *vo = &o;
    void *vp = &p;
    Base *vob = vo;
    Base *vobc = static_cast<Base*>(vo);
    Base *vobr = reinterpret_cast<Base*>(vo);
    Object *voo = vo;
    Object *vooc = static_cast<Object*>(vo);
    Object *voor = reinterpret_cast<Object*>(vo);
    Object *boo = bo;
    Object *booc = static_cast<Object*>(bo);
    Object *boor = reinterpret_cast<Object*>(bo);
    std::cout << "done" << std::endl;
    return 0;
}
