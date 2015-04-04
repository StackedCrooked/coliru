#include <iostream>
#include <string>



// Doesn't work because you can overload the structure reference operator `a.b.c.d` :(
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


/* */
struct SomeStruct {
   
    
    SomeStruct& then = *this;
    
    
    
    SomeStruct() {
        
    };
    
    class toggleClass {
        SomeStruct* someStructPointer;
        public:
            SomeStruct& then;
            
            bool getToggleState() {
                return someStructPointer->getToggleState();  
            };
            
            
            
            
            toggleClass(SomeStruct *i) : someStructPointer(i), then(*i) {
                //this->someStructPointer = &i;
            };
        
            // Setter
            SomeStruct& operator = (const SomeStruct i) {
                this->someStructPointer = (SomeStruct*)&i;
                this->then = i;
                return *this->someStructPointer;
                
            };
            // Setter
            SomeStruct& operator = (const SomeStruct *i) {
                this->someStructPointer = (SomeStruct*)i;
                this->then = *i;
                return *this->someStructPointer;
                
            };
            // Getter
            SomeStruct& operator -> () {
                this->someStructPointer->_toggle = !this->someStructPointer->_toggle;
                return *this->someStructPointer;
            };
            // Getter
            operator SomeStruct& () const {
                this->someStructPointer->_toggle = !this->someStructPointer->_toggle;
                return *this->someStructPointer;
            };
            
    } toggle{this};
    
    
    
    SomeStruct& operator = (const SomeStruct &other) {
        // protect against invalid self-assignment
        if (this != &other) {
            this->_toggle = other._toggle;
            
            this->toggle = other;
        }
        
         return *this;
    };
    
    
    bool getToggleState() {
        return this->_toggle;  
    };
    
    private:
        bool _toggle = false;
};
/* */




int main()
{
    SomeStruct asdf;
    std::cout << "asdf " << asdf.getToggleState() << std::endl;
    asdf.toggle;
    std::cout << "asdf " << asdf.getToggleState() << std::endl;
    bool result = asdf.then.toggle.then.toggle.then.toggle.then.getToggleState();
    
    
    std::cout << "asdf " << result << std::endl;
    
    return 0;
}


