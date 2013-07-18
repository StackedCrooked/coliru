class SomeClass
{
public:
    // Constructors & destructors.
    SomeClass();
    SomeClass(const SomeClass& other);
    SomeClass operator=(const SomeClass& other);
    SomeClass(const OtherClass& other); 
    ~SomeClass();
      
    // Functions that "do stuff" with this class.
    int SomeFunc();
    int OtherFunc();
    
    // Public member variables.
    int value; 

private:
    // Internal use functions. 
    int SomePrivateFunc();
    int OtherPrivateFunc();

    // Private member variables.
    int x, y; 
};