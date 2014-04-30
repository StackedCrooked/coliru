#include <iostream>
#include <string>
#include <vector>

int main()
{
    int charactorCount[3] = {3,5,8};
    int charactor[3][8] = {{3,2,4}, {3,1,3,4,1}, {1, 1, 1, 1, 1, 1, 1, 2}};

    int count = 3;
    std::cout << "테스트 횟수 : " << count << std::endl;
    
    int *list;
    int result =0;
    for ( int i = 0 ; i < count ; i++)
    {
        std::cout << "문자열 갯수 : " << charactorCount[i] << std::endl;
        list = new int[charactorCount[i]];
       
       
        std::cout << "문자열 입력 : " ;
        for( int j = 0; j < charactorCount[i] ; j++)
        {
            list[j] = charactor[i][j];
            std::cout << list[j] << " " ;
        }
        std::cout << std::endl;
        
        // result값 계산 구현
        
        std::cout << "최소값 : " << result << std::endl;
        delete list;
    }
    
    return 0;
}
