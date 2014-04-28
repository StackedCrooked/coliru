int main(int argc, const char * argv[])
{
    id (^iReturnStuff)() = ^id() {
        @try{} @catch(...){}
    };
    (void)iReturnStuff;
    
    id (^iReturnStuff2)() = ^id() {
        try{} catch(...){}
    };
    (void)iReturnStuff2;
    return 0;
}