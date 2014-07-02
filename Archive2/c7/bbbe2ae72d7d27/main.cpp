#include <memory>
#include <array>
#include <vector>

int main(){
    std::shared_ptr<int> ptr0 { new int(42) };
    std::shared_ptr<int> ptr1 { ptr0 };
    std::unique_ptr<int> uptr { new int(54) };
    
    int i{}; //i = 0
    int j{42};
    
    //on transmet une liste d'initialiseur en entrée
    std::array<int, 4> arr { { 42, 43, 44, 45 } };
    
    //pareil pour vector
    std::vector<int> v { {2, 10, 12 } };

    return 0;
}