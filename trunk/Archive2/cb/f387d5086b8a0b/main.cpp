#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<list>


int main()
{
    std::list<int> mylist = {5,2,9};
    mylist.push_back(6);
    mylist.push_back(8);
    
    std::list<int>::iterator itr = find(mylist.begin(),mylist.end(),9);
    
    std::cout <<"itr1 " <<  *itr <<std::endl;
    
    mylist.insert(itr,10); 
    
    itr++;
    
    std::cout <<"itr2 " << *itr <<std::endl;
    
    for(itr = mylist.begin();itr!=mylist.end();++itr)
        std::cout << *itr << " ";
    
    mylist.sort();
    
    //itr++;
    
    std::cout <<"itr3 " << *itr <<std::endl;
    
    for(itr = mylist.begin();itr!=mylist.end();++itr)
        std::cout << *itr << std::endl;
        
}
