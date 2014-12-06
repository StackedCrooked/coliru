#include <vector>
#include <iostream>

int sorted[] = {0,1,2,3,4,5,6,7,8,9,10};

void print(const std::vector<int>& data){ 
  for(int value : data)
    std::cout << value << " ";
  std::cout << "\n";
}

void split(int *dataIN, int dataSize){
    auto firstHalfSize = (dataSize + 1) / 2;
    std::vector<int> firstHalf(dataIN, dataIN + firstHalfSize); 
    std::vector<int> secondHalf(dataIN + firstHalfSize, dataIN + dataSize);

    std::cout << "firstHalf: ";
    print(firstHalf);
    std::cout << "seconHalf: ";      
    print(secondHalf);
}

int main(){
    split(sorted, sizeof(sorted)/sizeof(int));
}
