    #include <stdio.h>
    
    void hi(void) {
        puts("hi");
    }
    
    void bye(void) {
        puts("bye");
    }
    
    void moo(void) {
        puts("moo");
    
    }
    
    void dummy(int a, int b, int c) {}
    
    int main(void) {
        dummy((hi(),0), (bye(),0), (moo(),0));
    }