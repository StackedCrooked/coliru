#include <stdio.h>


class ID {
    
    private:
    int id;
    
    public:
    
    ID(int id) {
        this->id = id;
    }
    
    bool equals(ID& other) {
        return id == other.id;
    }
    
};


int main() {
    
    ID a(1), b(2), c(1);
    
    printf("a == b -> %s\na == c -> %s",
        a.equals(b) ? "true" : "false",
        a.equals(c) ? "true" : "false"
    );
}
