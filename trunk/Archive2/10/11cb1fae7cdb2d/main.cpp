#include <iostream>

class MyClass
{
    public:
    class MyIterator
    {
        public:
           const MyIterator& operator++(int) const;

        private:
            static const MyIterator END; 
    };

};

typedef MyClass::MyIterator MyIterator;

const MyIterator MyIterator::END = MyIterator(); 

const MyIterator& MyIterator::operator++(int) const 
{
    return MyIterator::END;
}

int main() {
    
}