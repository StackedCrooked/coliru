#include <vector>
#include <string>

class ClassWithConstMember
{
    public:
        const int m_const = 2;
        ClassWithConstMember(){}
        //ClassWithConstMember& operator=(const ClassWithConstMember& other){ return *this; }
        ~ClassWithConstMember(){}
};

int main(int argc, char** argv)
{
    std::vector<ClassWithConstMember> list;
    ClassWithConstMember c;
    list.push_back(c);
    
    std::vector<ClassWithConstMember>::iterator clIt = list.begin();
    while(clIt != list.end())
    {
        printf("%d\n", (*clIt).m_const);
        
        if(rand() % 2)
        {
            clIt = list.erase(clIt);
        }
        else
        {
            ++clIt;
        }
    }
}