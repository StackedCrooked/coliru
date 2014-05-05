#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print(std::vector<int> & in_list)
{
    for (std::vector<int>::iterator it=in_list.begin(); it!=in_list.end(); ++it)    
	{
		std::cout <<  *it << " ";
	}
	std::cout << std::endl;
}

int main()
{
    int charactorCount[3] = {3,5,8 };
    int charactor[3][48] = {{2,2,4}, {3,1,3,4,1}, {1, 1, 1, 1, 1, 1, 1, 2}};

    int count = sizeof(charactorCount)/sizeof(int);
    std::cout << "테스트 횟수 : " << count << std::endl;
    
    std::vector<int> list;
    int result = 0;
    for ( int i = 0 ; i < count ; i++)
    {
        result = 0;
        std::cout << "문자열 갯수 : " << charactorCount[i] << std::endl;
		list =  std::vector<int>(charactor[i], charactor[i] + charactorCount[i]);
              
        std::cout << "문자열 입력 : " ;
        print(list);
		
        // result값 계산 구현     
		for(unsigned int j = 0; j < list.size()-1 ; j++)
		{
			std::sort (list.begin() + j, list.end());

			// 정렬된 배열 출력
			//print(list);
			
			// 현재 값이 다음 값보다 작을 경우 더함
            if( list[j] <= list[j + 1])
            {   
				//std::cout << "sum : " << list[j] << " + " << list[j + 1];
                list[j + 1] += list[j];
				//std::cout << " = " << list[j + 1] ;

                result += list[j + 1];
				//std::cout << " total : " << result << std::endl;
            }

		}
		
        std::cout << "최소값 : " << result << std::endl;
    }
	    
    return 0;
}
