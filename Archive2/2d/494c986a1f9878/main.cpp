#include <iostream>
#include <vector>

class ComponentInterface {
    public:
    
    virtual int start() = 0;
    virtual int stop()  = 0;
    
    std::vector<std::function<int (int[], int[])>> commandsArray;
    
    int command(int commandId, int attrsList[], int responseList[]) {
        return commandsArray[commandId](attrsList, responseList);
    }
};

class Led : public ComponentInterface {

    public:
        Led(float* ledIntensity) {
            auto fn = std::bind(&Led::setIntensity, this, std::placeholders::_1, std::placeholders::_2);
            commandsArray.push_back(fn);
         }
         
        int setIntensity(int attrs[], int returns[]) {
            printf( "Set intensity called" );
            return 1;
        }

        int start() { return 0; }
        int stop()  { return 0; }

};


int main() {
    float ledIntensity = 0.5f;
    std::unique_ptr<ComponentInterface> ptr = std::make_unique<Led>(&ledIntensity);
    
    // Whatever
    int attrList[2];
    int responseList[2];
    ptr->command (0, attrList, responseList);
}