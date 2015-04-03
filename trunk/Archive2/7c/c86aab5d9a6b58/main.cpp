struct CantTouchThis {
    template <typename T> operator T() const { throw "computer says 'No.'"; }
};

int main() {
    CantTouchThis a, b;
    
    b = a;
    auto x = static_cast<CantTouchThis>(a); // ok
    //int  y = (int) a;                    // throws
    //int  z = static_cast<int>(a);        // throw
    
    (void) x; // doesn't throw! 
    (void) y, (void) z;
}
