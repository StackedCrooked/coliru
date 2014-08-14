

#include <atomic>
#include <stdint.h>

struct dataStruct {
};

int main() {
    std::atomic<dataStruct> atomicValue;
    atomicValue = dataStruct();
    atomicValue.load();
}

