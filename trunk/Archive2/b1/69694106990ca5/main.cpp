#include <iostream>
#include <string>


#include <math.h>



/* */
template <typename T>
struct Expect {
    struct ExpectFlags {
        bool negate = false;
    };
    
    
    Expect(T expected) {
        this->expected = expected;
    };
    
    Expect* equal(T other) {
        this->addTestResult(this->expected == other);
        
        return this;
    };
    
    Expect* equalWithinTolerance(T other) {
        return this->equalWithinTolerance(other, 0.0001);
    };
    Expect* equalWithinTolerance(T other, double tolerance) {
        this->addTestResult(abs(this->expected - other) <= tolerance);
        
        return this;
    };
    
    Expect* passTest(bool (*testFunc)(T expected, T actual), T actual) {
        this->addTestResult(testFunc(this->expected, actual));
        
        return this;
    };
    
    
    
    
    /* */
    class neverClass {
        Expect* expectPointer;
        public:
            neverClass(Expect *i) : expectPointer(i) {};
            
            // Setter
            Expect* operator = (const Expect i) {
                return this->expectPointer = (Expect*)&i;
                
            };
            // Setter
            Expect* operator = (const Expect *i) {
                return this->expectPointer = (Expect*)i;
            };
            Expect* operator -> () {
                this->expectPointer->flags.negate = !this->expectPointer->flags.negate;
                return this->expectPointer; 
            };
            // Getter
            operator Expect* () const {
                this->expectPointer->flags.negate = !this->expectPointer->flags.negate;
                return this->expectPointer;
            };
    } never{this};
    /* */

    
    // Provided as chainable getters to improve the readability of your assertions.
    // They do not provide testing capabilities.
    Expect* to = this;
    Expect* be = this;
    Expect* been = this;
    Expect* is = this;
    Expect* that = this;
    Expect* which = this;
    // `and` is a reserved keyword
    Expect* then = this;//Expect* and = this;
    Expect* has = this;
    Expect* have = this;
    Expect* with = this;
    Expect* at = this;
    Expect* of = this;
    Expect* same = this;
    
    
    
    bool getResult() {
        return this->_didPass;
    };
    
    operator bool() {
        std::cout << "resboolop " << this->_didPass << std::endl;
        return this->_didPass;
    };
    
    private:
        T expected;
        ExpectFlags flags;
        
        bool _didPass = true;
        
        void addTestResult(bool didPass) {
            this->_didPass = this->_didPass && (this->flags.negate ? !didPass : didPass);
            std::cout << "res " << this->_didPass << std::endl;
            
            // Reset the flag
            this->flags.negate = false;
        };
};
/* */




int main()
{
    std::cout << "Expect 1: " << Expect<int>(3).to->equal(3)->getResult() << std::endl;
    
    std::cout << "Expect 0: " << Expect<int>(3).to->never->be->equal(3)->getResult() << std::endl;
    
    std::cout << "Expect 0: " << Expect<int>(3).to->equal(5)->getResult() << std::endl;
    
    std::cout << "Expect 0: "<< Expect<int>(3).to->equal(5)->getResult() << std::endl;
    //Expect<float>(3).to->equalWithinTolerance(4);
}


