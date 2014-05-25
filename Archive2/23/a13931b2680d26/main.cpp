struct List {};

struct Component {
    virtual ~Component() = 0;
    
    friend List operator +(Component &c1, Component &c2) {
        List l;
    //    l.push(c1);
    //    l.push(c2);
        return l;
    }    
};

Component::~Component() {}

struct D : Component {};

int main() {
    D d1, d2;
    d1 + d2;
}