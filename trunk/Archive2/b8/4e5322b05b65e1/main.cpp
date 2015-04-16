    enum A { valueA = 1};
    
    enum B { 
        // if you change 0u to 0, there'll be no warning
        thisval = 0u, 
        // if you change valueA to any integral constant, there'll be no warning
        nextval = valueA, 
        // warning on this line
        value = nextval > thisval ? nextval : thisval,
        // no warning here
        value2 = nextval > thisval
    };
    
    int main() {
        // no warning here
        (void)(nextval > thisval ? nextval : thisval);
        // the same warning also here - but not on clang (it could really say something)
        (void)(nextval > thisval ? nextval : false);
    }
