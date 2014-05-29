#include <string>
#include <iostream>
#include <cstdio>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace boost;
using namespace boost::multi_index;
using namespace std;
class Employee
{
public:
    int id;
	string name;
	int age;

public:
	Employee(int id_,std::string name_,int age_):id(id_),name(name_),age(age_){}
	Employee(const Employee& e) :
		id(e.id), name(e.name), age(e.age)
		{
			printf("copy ctor called\n");
		}

	friend std::ostream& operator<<(std::ostream& os,const Employee& e)
	{
		os<<e.id<<" "<<e.name<<" "<<e.age<<std::endl;
		return os;
	}
};

typedef multi_index_container<
Employee,
indexed_by<
ordered_unique<member<Employee, int, &Employee::id> >,
ordered_non_unique<member<Employee, string, &Employee::name> >,
ordered_non_unique<member<Employee, int, &Employee::age> >
>
> EmployeeContainer;

typedef EmployeeContainer::nth_index<0>::type IdIndex;
typedef EmployeeContainer::nth_index<1>::type NameIndex;
typedef EmployeeContainer::nth_index<2>::type AgeIndex;

int main(){
	EmployeeContainer con;
	Employee a(0,"Joe",31);
	Employee b(1,"Robert",27);
	Employee c(2,"John",40);
	con.insert(a);
	con.insert(b);
	con.insert(c);

	IdIndex& ids = con.get<0>();
	copy(ids.begin(),ids.end(), ostream_iterator<Employee>(cout));
	cout << endl;

	NameIndex& names = con.get<1>();
	copy(names.begin(), names.end(), ostream_iterator<Employee>(cout));
	cout << endl;

	names.erase(names.begin());

	AgeIndex& ages = con.get<2>();
	copy(ages.begin(), ages.end(), ostream_iterator<Employee>(cout));
	cout << endl;

	return 0;
}