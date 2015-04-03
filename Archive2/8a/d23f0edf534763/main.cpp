#include <iostream>
#include <string>



/* */
// Chainable: SomeStruct().toggle->then->toggle->then->toggle->getToggleState() 
struct SomeStruct {
   
    SomeStruct() {
        this->then = this;
        
        this->toggle = this; 
    };
    
    /* */
    class {
        SomeStruct* someStructPointer;
        public:
            // Setter
            SomeStruct* operator = (const SomeStruct *i) {
                return this->someStructPointer = (SomeStruct*)i;
                
            };
            SomeStruct* operator -> () {
                return someStructPointer;
            };
            // Getter
            operator SomeStruct* () const {
                this->someStructPointer->_toggle = !this->someStructPointer->_toggle;
                return someStructPointer;
            };
    } toggle;
    /* */
    
    
    SomeStruct* then;
    

    bool getToggleState() {
        return this->_toggle;  
    };
    
    private:
        bool _toggle = false;
};
/* */




int main()
{
    SomeStruct mySomething;
    (SomeStruct*)mySomething.toggle;
    std::cout << mySomething.getToggleState() << std::endl;
    (SomeStruct*)mySomething.toggle;
    std::cout << mySomething.getToggleState() << std::endl;
    (SomeStruct*)mySomething.toggle;
    std::cout << mySomething.getToggleState() << std::endl;
    
    // Chainable
    std::cout << SomeStruct().toggle->then->toggle->then->toggle->getToggleState() << std::endl;
    
    return 0;
}


