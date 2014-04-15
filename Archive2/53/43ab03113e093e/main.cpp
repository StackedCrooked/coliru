#include <iostream>
#include <deque>

int main()
{
    std::deque<int> q;  
	q.push_back(1);
	std::deque<int>::iterator it = q.begin();
	q.push_back(2);
	std::cout << *++it << std::endl;
}
