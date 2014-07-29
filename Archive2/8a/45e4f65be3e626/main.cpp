#include <memory>
#include <iostream>

void FuckingCOM ( int** cominitializegogo ) {delete *cominitializegogo; *cominitializegogo = new int(48);}
void FuckingCOM2 ( int** cominitializegogo ) { /* blah blah complicated setup*/ *cominitializegogo = new int(48);}

int main () {    
    std::unique_ptr<int> meow( new int(24) );
    auto* ptr = meow.release();
    FuckingCOM2 ( &ptr );  
    meow.reset(ptr);
    std::cout << *meow << std::endl;
}