    #include <iostream>
    #include <string>

    struct Base { 
        virtual void print() {}
    };

    int main(int, char**) {
       std::cout <<"Start" << std::endl;
	   Base storage[1];
       storage[0].print();
    
       std::cout <<"Succeed" << std::endl;
	   return 0;
    }
