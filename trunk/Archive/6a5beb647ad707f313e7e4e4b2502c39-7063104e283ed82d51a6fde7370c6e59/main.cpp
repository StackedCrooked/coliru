#include <iostream>
#include <vector>

struct a
{
    std::vector<int> myvec;
};

int main()
{
	bool fail = false;

	for(int i = 0; ++i < 500;)
	{
		a* pA = new a;
		pA->myvec.resize(i+1);
		pA->myvec[i] = 10;

		void* pvA = static_cast<void*>(pA);
		pA = reinterpret_cast<a*>(pvA);

		if(pA->myvec[i] != 10)
		{
			fail = true;
			break;
		}

		delete pA;
	}

		if(fail)
			std::cout<<"FAILED!!";
		else
			std::cout<<"Never failed :/";
}