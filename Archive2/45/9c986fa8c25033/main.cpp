#include <iostream>

    using namespace std;
    class Numbers;

    class Numbers2
    {
    private:

    public:
        void getNumbers(Numbers &);
    };

    class Numbers
    {
    private:
        int num;
    public:
        Numbers(){num = 0;};
        friend void Numbers2::getNumbers(Numbers &);

    };

    void Numbers2::getNumbers(Numbers &numbs)
        {
            cout << numbs.num << endl;
        }

    int main()
    {
        Numbers num1;
        Numbers2 num2;

        num2.getNumbers(num1);
    }