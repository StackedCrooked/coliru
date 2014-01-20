#include <string>
#include <tuple>
#include <cstring>
#include <iostream>
#include <array>

struct A
{
    A() : m_data(0)
    {
        std::cout << "default construct, add:" << std::hex << this << " data:" << m_data << std::endl;
    }
    A(int data) : m_data(data)
    {
        std::cout << "construct, add:" << std::hex << this << " data:" << m_data << std::endl;
    }
    A(const A &a)
    {
        m_data = a.m_data;
        std::cout << "copy, add:" << std::hex << this << " data:" << m_data << std::endl;
    }
    A & operator = (const A & a)
    {
        m_data = a.m_data;
        std::cout << "asign, add:" << std::hex << this << " data:" << m_data << std::endl;
        return *this;
    }
    A(A &&a)
    {
        m_data = a.m_data;
        std::cout << "move, add:" << std::hex << this << " data:" << m_data << std::endl;
    }
    A & operator = (A && a)
    {
        m_data = a.m_data;
        std::cout << "move asign, add:" << std::hex << this << " data:" << m_data << std::endl;
        return *this;
    }
    ~A()
    {
        std::cout << "destroy, add:" << std::hex << this << " data:" << m_data << std::endl;
    }
    friend std::ostream& operator << (std::ostream &os, const A & data)
    {
        os << data.m_data << std::endl;
        return os;
    }
    int m_data;
};

template<typename... TArgsPack>
void GetMd5(TArgsPack&&... data)
{
  std::array<A, sizeof...(data)> vec{{(data)...}};
  for (auto &it : vec)
  {
      std::cout << it << std::endl;
  }
  //return *vec.begin();
}

using namespace std;

class cdr
{
public:
    template<class T>
    void GetData(T& a); //这里必须用引用，否则是拷贝传递，传进去的参数只是副本，你在函数内部做任何操作都是无效的

    void SetData(char* tdata);

    private:
    char _data[32];
};

void cdr::SetData(char* tdata)
{
    strcpy(_data,tdata);
}

template<class T>
void cdr::GetData(T& a)
{
    memcpy(&a,_data,sizeof(a));
}

struct charBuf
{
    char data[32];
};

int main()
{
    cdr instance;
    charBuf tbuf;

    instance.SetData("hello world");
    instance.GetData(tbuf);

//输出为啥不是 hello world
    cout<<tbuf.data<<endl;
    return 0;
}

