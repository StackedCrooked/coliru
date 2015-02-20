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
    
    for( int i = 1; i < 50; i++) {
        Fractional = Div(1,i);
        std::cout << "1/" << i << "= 0.";
        for(std::vector<int>::iterator it = Fractional.begin(); it != Fractional.end(); it++) {
            std::cout << *it;  
        }
        std::cout << std::endl;
    }
    
    
    return 0;
 
 
    
}



std::vector<int> Div(int num, int denom) {
 
    std::vector<int> digits;
    double fval = 1;
    double ival = 1;
    num = num * 10;
    std::string sDig = "";
    
    while(fval != 0) {       
        fval = modf(double(num)/double(denom),&ival);
     
        digits.push_back(int(ival));
        num = (num - (ival*denom))*10;
        sDig = sDig + std::to_string(int(ival));
        
        if( digits.size() % 20 == 0) {
            if(FindRep(sDig)) {
                std::cout << "Rep Found (" << sDig << ")" << std::endl;
                break;
            }
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
   
    int sPos = 0,sLen = 1, lPos=-1;
    int rCnt = 0;
    int tHold = 5;
    
    
    while( sPos != fractional.size() ) {
        std::string sub = fractional.substr(sPos,sLen);
        //std::cout << sPos << " " << sLen << std::endl;
        for(int i = fractional.find(sub,0); i != std::string::npos; i = fractional.find(sub,i)) {
        
            rCnt++;
           
            //std::cout << sPos << " " << sLen << " " << lPos <<  " " << i << " " << sub << std::endl;
        
        
            if( (lPos+sLen) != i ) {
                //std::cout << sLen << " " << i << std::endl;
                sLen = i;
                sub = fractional.substr(sPos, sPos + sLen);          
                rCnt = 0;
            
            }else if (i == std::string::npos) {
            
                std::cout << "Increment sPos" << std::endl;
             
            }
        
            lPos = i;
            i++;
            
        
            if(tHold <= rCnt) {
                fractional = sub;
                return true;
            }
            
      
        }
        
        rCnt = 0;
        lPos = sPos;
        if(sLen == 1) sPos++;
        
        
    }
    
    
    
    
    
    //std::cout << sub << std::endl;
    
 
    return false;
}

