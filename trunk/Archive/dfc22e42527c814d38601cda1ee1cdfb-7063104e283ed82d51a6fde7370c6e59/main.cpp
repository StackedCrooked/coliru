#include <iostream>
#include <string>
#include <vector>
#include <memory>

template <typename T, typename TDx= std::default_delete<T>, bool isarray = std::is_array<T>::value>
class ptr;

// Partial specialization
template <typename T, typename TDx>
class ptr<T, TDx, false> : private std::unique_ptr<T, TDx> {
};

template <typename T, typename TDx>
class ptr<T, TDx, true> : private std::unique_ptr<T, TDx> {
};


int main() {
    
}