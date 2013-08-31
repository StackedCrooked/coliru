#include <iostream>
#include <functional>

struct id{
    id(int hold, std::function<void(int)> deleteWith):
        held_id(hold), deletor(deleteWith){};
    ~id(){
        deletor(held_id);
    }
    int held_id;
    std::function<void(int)> deletor;
};

void deletor_a(int id){
    std::cout << "I'm delete_a and you held : " << id << "\n";
}

namespace{
    void deletor_b(int id){    
        std::cout << "I'm delete_b and you held : " << id << "\n";
    }
}

int main() {
    id(5, std::move(deletor_a));
    id(666, deletor_b);
}

