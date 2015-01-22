#include <iostream>
using std::cin;using std::cout;using std::endl;
class CStudent;
class CTeacher
{
public:
void ModifyScore(CStudent &Student1);
};
class CStudent
{
private:
int m_fscore;
public:
void print()
{
    cout << "student score is " << m_fscore << endl;
}    
friend void CTeacher::ModifyScore(CStudent &Student1);
};
void CTeacher::ModifyScore(CStudent &Student1)
{
int score;
cout << "input score" << endl;
cin >> score;
Student1.m_fscore = score;
}
int main()
{
    CStudent s;
    CTeacher t;
    t.ModifyScore(s);
    s.print();
    return 0;
}