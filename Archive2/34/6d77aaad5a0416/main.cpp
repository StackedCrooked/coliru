struct foo { 
    template<typename T> 
    void lol(T) {} 
};

int main() {
    foo x;
    x.lol(10);
    x.lol('a');
}