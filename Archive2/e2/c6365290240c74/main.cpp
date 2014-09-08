#include<iostream>
#include<string>
using namespace std;

class Employee
{
    string empName;
    string empHireDate;
    int empNo;
public:
    Employee(string en, string eh, int n)
    {
        setEmployeeName(en);
        setEmployeeHireDate(eh);
        setEmployeeNo(n);
    }
    void setEmployeeName(string ename)
    {
        empName=ename;
    }
    void setEmployeeHireDate(string hd)
    {
        empHireDate=hd;
    }
    void setEmployeeNo(int no)
    {
        empNo=no;
    }
    string getEmployeeName() const
    {
        return empName;
    }
    string getEmployeeHireDate() const
    {
        return empHireDate;
    }
    int getEmployeeNo() const
    {
        return empNo;
    }
};

class ProductionWork:public Employee
{
    int shift;
    double hourPayrate;
public:
    ProductionWork(int s, double payr,string name,string hiredate, int eno):Employee(name,hiredate,eno)
    {
        if(s==1 || s==2)
            shift=s;
        hourPayrate=payr;
    }
    void setShift(int s)
    {
        if(s==1 || s==2)
            shift=s;
    }
    void setPayRate(double p)
    {
        hourPayrate=p;
    }
    int getShift() const
    {
        return shift;
    }
    double getPayRate() const
    {
        return hourPayrate;
    }
    friend ostream&operator<<(ostream& out, ProductionWork& pw);
};


int main()
{
    ProductionWork pw(2,40,"Hussain","21-04-2014",452);
    cout<<pw;
    system("pasue");
    return 0;
}

ostream& operator<<(ostream& out, ProductionWork& pw)
{
    out<<"\nEmployee Name:"<<pw.getEmployeeName<<"\tHiredate:"<<pw.getEmployeeHireDate;
    out<<"\nEmployee Number:"<<pw.getEmployeeNo<<"\tShift:"<<pw.getShift<<"\tPay Rate:"<<pw.getPayRate;
    out<<"\n\n";
    return out;
}