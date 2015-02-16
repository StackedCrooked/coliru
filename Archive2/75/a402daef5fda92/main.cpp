#include <iostream>
#include <vector>
#include <math.h>
#include <string>



std::vector<int> Div(int,int);
std::string Rep(std::vector<int>);
bool FindRep(std::string&);

int main() {
    
    std::cout << std::endl;
    
    
    std::vector<int> Fractional;
    
    
    Fractional = Div(1,7);
    
    std::cout << "0.";
    
    for(std::vector<int>::iterator it = Fractional.begin(); it != Fractional.end(); it++) {
        std::cout << *it;  
    }
    
    
    return 0;
 
 
    
}



std::vector<int> Div(int num, int denom) {
 
    std::vector<int> digits;
    double fval = 1;
    double ival = 1;
    num = num * 10;
    std::string sDig = "";
    
    while(digits.size() < 50 && fval != 0) {       
        fval = modf(double(num)/double(denom),&ival);
        //std::cout << ival << ' ' << fval << std::endl;
        digits.push_back(int(ival));
        num = (num - (ival*denom))*10;
        //std::cout << Rep(digits) << std::endl;
        sDig = sDig + std::to_string(int(ival));
        //std::cout << sDig << std::endl;
        if(FindRep(sDig)) {
            std::cout << sDig << std::endl;
            break;
        }
    }
    
    return digits;
}

std::string Rep(std::vector<int> Digs) {
   
    std::string ThisFrac = "";
  
    for(std::vector<int>::iterator it = Digs.begin(); it != Digs.end(); it++) {
        ThisFrac = ThisFrac + std::to_string(*it);
    }
    
    
    
   
    return ThisFrac; 
}

bool FindRep(std::string & fractional) {
    std::cout << fractional << std::endl;
    int sPos,sLen = 0,1;
    std::string sub = fractional.substr(sPos,sPos+sLen);
    
    std::cout << sub << std::endl;
    
 
    return false;
}

