#include <iostream>
#include <cctype>
std::string uncompress(const std::string& in){
    int number=0,place=0;
    std::string returnable;
    for(auto ch : in){
        if(isalpha(ch)){
            if(number){
                for(int i = 0;i<number;i++){
                    returnable+=ch;
                }
                number = 0;
                place = 0;
            }
            else{
                returnable+=ch;
            }
        }
        else if(isdigit(ch)){
            if(!place){
                number=ch-'0';
            }
            else{
                number+=(10*(place))*(ch-'0');
            }
            place++;
        }
    }
    return returnable;
}
int main(int argc, char **argv){
    std::cout<<uncompress("a55bc");    
    return 0;
}