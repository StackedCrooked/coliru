#include <iostream>

class Table{
    public:
    Table(){};
    };

void f(int i){
 static Table tbl;
if(i){
static Table tbl1;
std::cout<<i<<std::endl;
}
}

int main(){
f(0);
f(1);
f(2);

return 0;
}
