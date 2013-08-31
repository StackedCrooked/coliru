#include <iostream>


class A { public:
    int     gate_type :  4;
    bool storage_elem :  1;
    uint8_t privilege :  2;
    bool      present :  1;
} __attribute__((packed));

class B { public:
    struct Sub {
        int     gate_type :  4;
        bool storage_elem :  1;
        uint8_t privilege :  2;
        bool      present :  1;
    } type_attr; //Also tried with "__attribute__((packed))" here in addition to outside
} __attribute__((packed));


int main(){
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
}