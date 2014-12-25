#include <iostream>
#include <string>

struct Thing {
    std::string name;
    int width, length, height, mass;
    Thing (const std::string& n) : name(n) {}
    Thing (const std::string& n, int w, int l, int h, int m) :
        name(n), width(w), length(l), height(h), mass(m) {}
    Thing(const Thing& t) :
        name(t.name), width(t.width), length(t.length),
        height(t.height), mass(t.mass) {}
    void print() const {std::cout << name << ", " << width << ", " << length << ", " << height << ", " << mass << '\n';}
};

struct Clone : virtual Thing {
    Thing parent;
    Clone (const std::string& name, Thing p) : Thing(name), parent(p) {}
};

template <typename T>
struct ClonedType : public Clone, public T {
    ClonedType (const std::string& name, Thing t) :
        Thing(name), Clone(name, t), T(name) {}
};

// virtual inheritance needed because of ClonedType<Blob> being instantiated:
struct Blob : virtual Thing {
    Blob (const std::string& name) : Thing(name, 3, 4, 5, 20) {}
};

int main() {
    Blob blob("Blob");
    ClonedType<Blob> b("New Blob", blob);
    blob.print();  // Blob, 3, 4, 5, 20
    b.print();  // New Blob, -1, -1, 4237013, 0  // Here's the problem!
}