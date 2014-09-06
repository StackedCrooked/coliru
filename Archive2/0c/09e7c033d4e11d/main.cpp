    #include <iostream>
    bool foo = false;
    int addNumbers(int x, int y)
    {
        int answer = x;
        answer = 1;
        //return x + y;
    }
    
    int main(){
      if(!foo) {
        std::cout << 1 << std::endl;
        addNumbers(10, 20);
      }
      else {
        std::cout << 2 << std::endl;
      }
    }