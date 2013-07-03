
template<int N>
struct Lounge {
    
};


struct dumb {    
    constexpr int operator++(int){
        return 42;
    }
};


int main() {
    dumb C;
    Lounge<C++> cpp;
}

