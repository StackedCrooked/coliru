#include <iostream> 
using namespace std;

int main()
{

    int bal, no1=0, no2=0, no3=0, no4=0, no5=0, no6=0, no7=0;
    cin >> bal;
    while (bal > 0 && bal < 1000000)
    {

        for (; bal >= 100;)
        {
            (bal - 100);
            no1++;
            if (bal < 100)
                break;
        }
        for (; bal >= 50;)
        {
            (bal - 50);
            no2++;
            if (bal < 50)
                break;
        }
        for (; bal >= 20;)
        {
            (bal - 20);
            no3++;
            if (bal < 20)
                break;
        }
        for (; bal >= 10;)
        {
            (bal - 10);
            no4++;
            if (bal < 10)
                break;
        }
        for (; bal >= 5;)
        {

            (bal - 5);
            no5++;
            if (bal < 5)
                break;
        }
        for (; bal >= 2;)
        {
            (bal - 2);
            no6++;
            if (bal < 2)
                break;
        }
        for (; bal >= 1;)
        {
            (bal - 1);
            no7++;
            if (bal < 1)
                break;
        }
        cout << no1 << " nota(s) de R$ 100,00" << endl;
        cout << no2 << " nota(s) de R$ 50,00" << endl;
        cout << no3 << " nota(s) de R$ 20,00" << endl;
        cout << no4 << " nota(s) de R$ 10,00" << endl;
        cout << no5 << " nota(s) de R$ 5,00" << endl;
        cout << no6 << " nota(s) de R$ 2,00" << endl;
        cout << no7 << " nota(s) de R$ 1,00" << endl;
    }

    return 0;
}
c++