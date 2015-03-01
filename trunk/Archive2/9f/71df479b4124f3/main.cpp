#include <iostream>
#include <array>
#include <memory>

struct employee
{
    virtual ~employee() = default;
};

struct accounter : employee {};

typedef std::unique_ptr<employee> p_employee;

std::array<p_employee, 4> make_test_array() {
    std::array<p_employee, 4> objects = {{
        p_employee(new accounter()),
        p_employee(new accounter()),
    }};
    
    objects[2].reset(new accounter());
    objects[3] = p_employee(new accounter());
    return objects;
}

int main()
{
    auto arr = make_test_array();
}
