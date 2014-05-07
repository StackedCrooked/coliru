#include <iostream>
#include <string>
#include <algorithm>


void sort(int * in_list, int in_count)
{
    for(int i = 0 ; i < in_count - 1 ; i++)
    {
        for( int j = i + 1 ; j < in_count ; j++)
        {
            if( in_list[i] >  in_list[j])
            {
                std::swap(in_list[i], in_list[j]);
            }
        }        
    }
}

void print(int * in_list, int in_count)
{
    for(int i = 0; i < in_count ; i++)
	{
		std::cout <<  in_list[i] << " ";
	}
	std::cout << std::endl;
}


int main()
{    
    int charactorCount[3] = {3,5,8};
    int charactor[3][8] = {{2,2,4}, {3,1,3,4,1}, {1, 1, 1, 1, 1, 1, 1, 2}};

    int count = sizeof(charactorCount)/ sizeof(int);
    std::cout << "테스트 횟수 : " << count << std::endl;
    
    int *list;
    int result = 0;
    for ( int i = 0 ; i < count ; i++)
    {
        result = 0;
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
		for( int j = 0; j < charactorCount[i] ; j++)
		{
			sort(&list[j], charactorCount[i] - j);

			// 정렬된 배열 출력
			print(list, charactorCount[i]);
			
			// 현재 값이 다음 값보다 작을 경우 더함
            if( list[j] <= list[j + 1])
            {   
				std::cout << "sum : " << list[j] << " + " << list[j + 1];
                list[j + 1] += list[j];
				std::cout << " = " << list[j + 1] ;

                result += list[j + 1];
				std::cout << " total : " << result << std::endl;
            }

		}
		
        std::cout << "최소값 : " << result << std::endl;
        delete list;        
    }
	    
    return 0;
}
