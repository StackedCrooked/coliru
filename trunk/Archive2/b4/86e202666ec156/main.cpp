    #include <iostream>
    #include <string>

    struct Base { 
        virtual void print() {}
    };

    struct Derived : Base {
        void print() {}
    };

    int main(int, char**) {
	   Derived storage[1];
       storage[0].print();
    
       std::cout <<"Succeed";
	   return 0;
    }
