#include <iostream>
#include <string>


#include <math.h>



/* * /
// myThing.expect().to->be->equal();
struct SomeStruct {
    SomeStruct() {
        this->to = this;
        this->be = this;
    };

    SomeStruct expect() {
        return *this;
    };
    SomeStruct equal() {
        return *this;
    };
    
    SomeStruct* to;
    SomeStruct* be;
};
/* */



/* */
// myThing.expect()->to->be->equal();
struct SomeStruct {
    SomeStruct() {
        this->to = this;
        this->be = this;
    };
    
    SomeStruct* expect() {
        return this;
    };
    SomeStruct* equal() {
        return this;
    };
    
    SomeStruct* to;
    SomeStruct* be;
};
/* */


/* */
template <typename T>
struct Expect {
    struct ExpectFlags {
        bool negate = false;
    };
    
    
    Expect(T expected) {
        this->to = this;
        this->be = this;
        this->been = this;
        this->is = this;
        this->that = this;
        this->which = this;
        // `and` is a reserved keyword
        this->then = this;//this->and = this;
        this->has = this;
        this->have = this;
        this->with = this;
        this->at = this;
        this->of = this;
        this->same = this;
        
        
        this->never = this;
        
        this->expected = expected;
    };
    
    Expect* equal(T other) {
        this->didPass = this->didPass && (this->expected == other);
        
        return this;
    };
    
    Expect* equalWithinTolerance(T other) {
        return this->equalWithinTolerance(other, 0.0001);
    };
    Expect* equalWithinTolerance(T other, double tolerance) {
        this->didPass = this->didPass && (abs(this->expected - other) <= tolerance);
        
        return this;
    };
    
    Expect* passTest(bool (*testFunc)(T expected, T actual), T actual) {
        this->didPass = this->didPass && testFunc(this->expected, actual);
        
        return this;
    };
    
    operator bool() {
        return this->didPass;
    };
    
    
    /* */
    class {
        Expect* expectPointer;
        public:
            // Setter
            Expect* operator = (const Expect *i) {
                this->expectPointer = (Expect*)i;
                this->expectPointer->flags.negate  = !this->expectPointer->flags.negate;
                
                return this->expectPointer;
                
            };
            // Getter
            operator Expect* () const { return expectPointer; };
    } never;
    /* */

    
    
    // Provided as chainable getters to improve the readability of your assertions.
    // They do not provide testing capabilities.
    Expect* to;
    Expect* be;
    Expect* been;
    Expect* is;
    Expect* that;
    Expect* which;
    // `and` is a reserved keyword
    Expect* then;//Expect* and;
    Expect* has;
    Expect* have;
    Expect* with;
    Expect* at;
    Expect* of;
    Expect* same;
    
    
    
    private:
        T expected;
        ExpectFlags flags;
        
        bool didPass = false;
};
/* */




int main()
{
    SomeStruct myThing;
    myThing.expect()->to->be->equal();
    
    bool result = Expect<int>(3).to->be->equal(3);
    std::cout << result << std::endl;
    bool result2 = Expect<int>(3).to->never->be->equal(3);
    std::cout << result2 << std::endl;
    //Expect<float>(3).to->equalWithinTolerance(4);
}


