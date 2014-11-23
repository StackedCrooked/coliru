#include <iostream>
#include <vector>

#ifdef REAL
    typedef double  elem_type;
#else
    typedef int     elem_type;
#endif

int main()
{
    std::vector<elem_type>  vector;
    
    while(true)
    {
        elem_type elem;
        std::cin >> elem;
        if (elem == 0)
            break;
        vector.push_back(elem);
    }
    
    std::vector<elem_type>::iterator iter = vector.begin();
    elem_type max = *iter;
    do 
    {
    max = (*iter > max ? *iter : max);
        std::cerr << *(iter++) << " ";
    } while(iter != vector.end());
    std::cerr << std::endl;    

    iter = vector.begin();
    elem_type number = *iter;
    *iter = max; iter++;
    while (max != *iter)
    {
    	elem_type tmp;
    	tmp = *iter;
    	*iter = number;
    	number = tmp;	
    	iter++;	
    }
    *iter = number;

    std::cerr << max << " ";
    for (iter = vector.begin() + 1; iter != vector.end(); iter++)
    {
    	*iter = *iter - *(iter - 1);
    	std::cerr << *iter << " ";
    }
    std::cerr << std::endl;
   

}