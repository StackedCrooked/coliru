#include <iostream>
using namespace std;
class Time
{
    private:
        int age;
        string name;
    public:
        void setAge(int age)
        {
            this->age = age;
        }
        int getAge()
        {
            return this->age;
        }
};
int main()
{
    Time t1;
    int tmp = 0;
    cin>>tmp;
    t1.setAge(tmp);
    cout <<t1.getAge()<<endl;
    return 0;
}
