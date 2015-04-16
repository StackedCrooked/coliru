enum A { valueA = 1};

enum B { 
    // if you change 0u to 0, there'll be no warning
    thisval = 0u, 
    // if you change valueA to any integral constant, there'll be no warning
    nextval = valueA, 
    // warning on this line
    value = nextval > thisval ? nextval:thisval
};


int main() {
    // this line doesn't produce a warning
    if (nextval > thisval){}
}
