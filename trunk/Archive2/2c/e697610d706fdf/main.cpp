#include <cassert>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>

struct field {
    std::size_t offset;
    std::size_t size;
};

struct type {
    std::vector<field> fields;
};

struct object {
    type* isa;

    template<typename T>
    void set_field(std::size_t index, T value) {
        assert(sizeof(value) == isa->fields[index].size);
        std::memcpy(reinterpret_cast<char*>(this) + isa->fields[index].offset, &value, sizeof(value));
    }

    template<typename T>
    T get_field(std::size_t index) {
        assert(sizeof(T) == isa->fields[index].size);
        T result;
        std::memcpy(&result, reinterpret_cast<char*>(this) + isa->fields[index].offset, sizeof(T));
        return result;
    }
};

int main() {
    auto obj = static_cast<object*>(operator new(32));
    obj->isa = new type;
    obj->isa->fields = { { 8, 4 }, { 12, 4 }, { 16, 8 } };
    obj->set_field(0, std::uint32_t(1));
    obj->set_field(1, std::uint32_t(2));
    obj->set_field(2, std::uint64_t(3));
    std::cout << obj->get_field<std::uint32_t>(0) << '\n';
    std::cout << obj->get_field<std::uint32_t>(1) << '\n';
    std::cout << obj->get_field<std::uint64_t>(2) << '\n';
    return 0;
}