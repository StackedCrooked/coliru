#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

typedef std::shared_ptr<std::vector<char>> SerializedBytes;

int main()
{
    std::vector<char> list1{'a', 'b'};
    std::vector<char> list2{'c', 'd'};
    std::vector<char> list3{'e', 'f'};
    
    std::vector<std::vector<char>> bucket;
    bucket.push_back(list1);
    bucket.push_back(list2);
    bucket.push_back(list3);
    
    
    SerializedBytes serializedBytes = SerializedBytes (new std::vector<char> (6));


    for (std::vector<char>::iterator it = serializedBytes->begin (); it < serializedBytes->end ();) {
        for (auto serializedBytesInBucket : bucket) {
            for (size_t i = 0; i < serializedBytesInBucket.size (); i++) {
                (*it) = serializedBytesInBucket.at(i);
                it++;
            }
        }
     }
         
   for(const auto& elem : *(serializedBytes.get())) std::cout << elem << std::endl;
        
    
}