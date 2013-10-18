#include <iostream>
using namespace std;

// modified largely from
// http://d.hatena.ne.jp/toburau/20090722/1248283158

/*
class Test {
public:
    Test& operator=(const Test& rhs);
};
Test& Test::operator=(const Test& rhs)
{
    if (this == &rhs) return *this;          // *****
};
*/

//-----------------------------------------------------

class Data
{
    int num;
public:
    Data(void) : num(0) { }
    Data(int _num) : num(_num) { }
    Data(const Data &rhs) {
        cout << "copy constructor is called" << endl;
        num = rhs.num;
    }
    void show(void) {
        cout << num << endl;
    }
};

class CopyTest {
    Data *m_pData;
public:
    CopyTest(void) {
        m_pData = new Data(0);
    }
    CopyTest(int _num) {
        m_pData = new Data(_num);
    }
    void show(void) {
        m_pData->show();
    }
    CopyTest& operator=(const CopyTest& rhs);
};

CopyTest& CopyTest::operator=(const CopyTest& rhs) /*****/
{
    Data *p = m_pData;
    m_pData = new Data(*rhs.m_pData); // case 0 // OK // copy constructor is called
//  m_pData = new Data(*(rhs.m_pData)); // case 1 // OK
//  m_pData = new Data(*(rhs).m_pData)); // case 2 // NG
    delete p;
    return *this;
}


int main() {
    CopyTest cpyObjA, cpyObjB(31);

    cpyObjA.show();
    cpyObjB.show();

    cout << "## after" << endl; 
    cpyObjA = cpyObjB;
    cpyObjA.show();
    cpyObjB.show();

    return 0;
}