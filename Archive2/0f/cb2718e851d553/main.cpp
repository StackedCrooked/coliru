#include <string>

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
struct Expect {
    Expect() {
    };
    
    Expect* equal() {
        return this;
    };
    
    Expect* to;
    Expect* be;
};
/* */



int main()
{
    SomeStruct myThing;
    myThing.expect()->to->be->equal();
    
    Expect().to->be->equal();
}


