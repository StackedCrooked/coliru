#include <vector>
#include <iostream>
 



// you can also use includes, for example:
// #include <algorithm>
#include <cmath> 

#define UPPER_LIMIT 100000000

bool isAdjacent(int a, int b, int c);
int distance(int pValue, int qValue);

int solution(const std::vector<int> &A) {
    // write your code here...
    int largestDistance = -2; //default as the error condition for no adjacent pair found
    for (size_t p = 0; p < A.size(); ++p)
    {
        for (size_t q = 0; q < A.size(); ++q)
        {
            for (size_t v = 0; v < A.size(); ++v)
            {
                if (isAdjacent(A[p], A[v], A[q]))
                {
                    int tempDistance = distance(A[p], A[q]);
                    if (largestDistance < tempDistance)
                    {
                        largestDistance = tempDistance;
                    }
                }
        
            }
        }
    }
    if (largestDistance > UPPER_LIMIT)
    {
        largestDistance = -1; //error condition
    }

    return largestDistance;
}

bool isAdjacent(int a, int b, int c)
{
    return ((a < b  && b < c) || (a > b && b > c));
}

int distance(int pValue, int qValue)
{
    return std::abs(pValue - qValue);
}

int main()
{
    std::vector<int> numbers {2, 4, 6, 8};
 
    std::cout << "Solution:" << solution(numbers) << std::endl;
    std::cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = 5;
 
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}

