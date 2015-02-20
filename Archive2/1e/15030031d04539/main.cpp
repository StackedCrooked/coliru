#include <memory>

class Object
{
public:
     class ObjectBuilder; // the implementation of this file resides at the file where the Object class is
};


template<class> class TD;

class Object::ObjectBuilder
{
public:
void sampleFunction(){this; TD<decltype(this)> d; } // here this still means ::Object. I wanted 'this' to refer to 'Object::ObjectBuilder' instance
};
int main()
{
    
}