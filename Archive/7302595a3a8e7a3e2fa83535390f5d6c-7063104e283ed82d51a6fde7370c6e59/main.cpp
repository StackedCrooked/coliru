#include <iostream>

struct a
{
    int shiftdata[378];
	int m_int;
};

int main()
{
		a xA;
		xA.m_int = 10;

		void* pvA;
		a* pA2 = &xA;

		bool fail = false;

		for(int i = 0; ++i < 5000;)
		{
			pvA = static_cast<void*>(pA2);
			pA2 = reinterpret_cast<a*>(pvA);

			if(pA2->m_int != 10)
			{
				fail = true;
				break;
			}
		}

		if(fail)
			std::cout<<"FAILED!!";
		else
			std::cout<<"Never failed :/";
}