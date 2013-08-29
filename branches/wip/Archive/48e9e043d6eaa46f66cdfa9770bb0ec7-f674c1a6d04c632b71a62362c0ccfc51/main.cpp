class Class {
private:
    static int next_id;
public:
    Class();
    const int m_id;
};

int Class::next_id;

Class::Class() :m_id(next_id++)
{}

#include <iostream>

int main() {
    Class alice;
    Class bob;
    Class carol;
    std::cout << alice.m_id << ' ' << bob.m_id << ' ' << carol.m_id << '\n';
}
