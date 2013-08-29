#include <iostream>

struct a
{
    int* m_array;
};

int main()
{
	bool fail = false;

	for(int i = 0; ++i < 5000;)
	{
		a* pA = new a;
		pA->m_array = new int [i+1]; // A new size of data on every try
		pA->m_array[i] = 10;

		void* pvA = static_cast<void*>(pA);
		pA = reinterpret_cast<a*>(pvA);

		if(pA->m_array[i] != 10)
		{
			fail = true;
			break;
		}

		delete []pA->m_array;
		delete pA;
	}

		if(fail)
			std::cout<<"FAILED!!";
		else
			std::cout<<"Never failed :/";
}