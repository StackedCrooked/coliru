int main(int argc, const char * argv[])
{
    id (^iReturnStuff)() = ^id() {
        @try{} @catch(...){}
        //if you comment out line 4, Clang will not compile this.
        //if you leave it like this, Clang will compile and run this, even though
        //there's no value being returned.
        //is there something special in @try{} that turns off compiler errors?
    };
    (void)iReturnStuff;
    
    id (^iReturnStuff2)() = ^id() {
        try{} catch(...){}
        //if you comment out line 4, Clang will not compile this.
        //if you leave it like this, Clang will compile and run this, even though
        //there's no value being returned.
        //is there something special in @try{} that turns off compiler errors?
    };
    (void)iReturnStuff2;
    return 0;
}