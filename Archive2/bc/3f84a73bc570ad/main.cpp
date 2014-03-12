#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>

struct Data {
    int a;
    std::string b;
    float c;
};

Data* check;

std::string* allocateDataAndGetString() {
    check = new Data;
    return &check->b;
}

Data* getBaseDataPtrFromString(std::string* mStringMember) {
    static_assert(std::is_standard_layout<Data>::value,
                  "offsetof() only works on standard-layout types.");
    return reinterpret_cast<Data*>(reinterpret_cast<char*>(mStringMember) - offsetof(Data, b));
}

int main() {
    std::string* stringPtr(allocateDataAndGetString());
    Data* dataPtr{getBaseDataPtrFromString(stringPtr)};
    std::cout << "member = " << stringPtr << '\n'
              << "base = " << dataPtr << '\n';
    assert(dataPtr == check);
}
