#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>






void mprintf(int porttouse, std::string s){
       std::cout <<porttouse << ":" << s << std::endl; 
}

class Logger{
    int portToUse;
    std::string logLine;
    
       public:
    Logger(int32_t portToUse) : portToUse(portToUse){        
    }
    Logger(std::string logLine) : logLine(logLine){
        
    }
    std::string GetLine(){
     return this->logLine;   
    }
    ~Logger(){
    //    std::cout <<  " *Destruct* ";
     mprintf(portToUse, logLine);
    }
    
    template <class T>
    Logger& operator<<(T s){

        logLine += s;
        return *this;
    }
   
};



int main()
{
    Logger(1) << "test " << " anothertest";
std::cout << "after destruct";
//some logic
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Logger(5) << "test";
}


