#include <iostream>

int main()
{
    const int arrayCount = 1;
    const int arrayOfValues [arrayCount] = {0};
    
    int indexToReturn;
    int indexValue;
    int newValue;
    for (int i = 0; i < arrayCount; i++) {
        newValue = arrayOfValues[i];
        if (newValue >= indexValue) {
#if 1 // code added
            //std::cout << "indexValue=" << indexValue << std::endl;
            //std::cout << "newValue=" << newValue << std::endl;
            std::cout << "(newValue >= indexValue)=" << (newValue >= indexValue) << std::endl;
#endif
            indexToReturn = i;
            indexValue = newValue;
        }
    // At the end of this loop the value you want is indexToReturn
    }
    std::cout << "indexToReturn=" << indexToReturn << std::endl;
}
