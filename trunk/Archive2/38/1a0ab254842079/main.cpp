#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

/***this is a basic class,it's objects can carry a variety of office tasks,**/
/***used to intialize employee tasks****/
struct Task {
    Task():mytask("") {}
    Task(std::string new_task):mytask(new_task) {};
    std::string mytask;
    bool done=false;
};

/**************Employee class*********************/
class employee
{
private:
    std::string name;
    std::string message {""};
    std::vector<Task> mytasks {0};
    std::size_t failed_tasks;
    bool warned=false;
    bool tobe_fired=false;
    bool fired=false;
    int days;
    bool check_failing();
public:
    /***------------used constructor-----------------------------------***/
    employee(const std::string& nm,const std::vector<Task> vec)
        :name(nm),mytasks(vec.begin(),vec.end()),failed_tasks(0),days(0) {}

    /***-------------getters--------------------------------------------***/
    bool to_be_fired() const
    { return tobe_fired; }

    bool got_fired() const
    { return fired; }

    int getdays() const
    { return days; }

    bool blacklist() const
    { return(warned&&days>=3); }

    std::string getname() const
    { return name; }

    /***-------------setters---------------------------------------------***/
    void work();
    void setfired();
    void receive_mssg(const std::string mssg);
};

///@param string, @brief receives a message sent from mananger
///it also sets the warned variable to true, this variable is
/// used by blacklist member function
void employee::receive_mssg(const std::string mssg)
{
    if(warned) {}
    else {
        message=mssg;
        warned=true;
        days=1;
    }
}

///@param void, @brief checks if an employees failed to accomplish more than 2
/// tasks, each employee will have atleast six tasks
bool employee::check_failing()
{
    static std::mt19937_64 rg(time(nullptr));
    static std::uniform_int_distribution<> dist(3, 8);
    int hrs_to_wrk= dist(rg);///each emp must always accomplish more than 3 tasks

    if(got_fired())
        return false;

    for(unsigned int i=0; i<mytasks.size()&&i<hrs_to_wrk; i++)
        mytasks[i].done=true;

    for(const auto tsk: mytasks)
        if(!tsk.done)
            ++failed_tasks;

    return (failed_tasks>=2);
}

///@param void, @brief simulates work progress, each day failed is counted, if
///failed days accumlate to five, the employee should be fired by the mananger
void employee::work()
{
    if(!got_fired()) {
        if(days>=5) {
            tobe_fired=true;
        } else {
            if(check_failing()) {
                ++days;
            }
        }
    }
}

///@param void, sets the "fired" variable to true, function is only used
/// by mananger to fire employees
void employee::setfired()
{ fired=true; }
#endif // EMPLOYEE_H



#ifndef MANAGER_H
#define MANAGER_H


/*******Manager Class***************/
class manager
{
private:
    std::string name;
    double salary;
    std::vector<employee> mylist;
    void evaluate();
    void send_mssg(const std::string& message,employee& emp);
public:
    manager(const std::string& nm,double amnt,const std::vector<employee> vec)
        :name(nm),salary(amnt),mylist(vec.begin(),vec.end()) {}
    void monitor();
    void show() const;
};

///@param string massage, employee object
///@brief the message is sent to the employee obbject via the employee
///member receive_mssg() function, send_mssg() is a private member
void manager::send_mssg(const std::string& message,employee& emp)
{
    emp.receive_mssg(message);
}

///@param void
///@brief private member function, used by the public function
///monitor to evaluate an employee working progress, used to fire empployees
void manager::evaluate()
{
    for(auto& wrk: mylist)
        wrk.work();

    for(auto& i: mylist)
        if(i.got_fired())
            ;
        else if(i.to_be_fired())
            i.setfired();
        else if(i.getdays()>2)
            send_mssg(std::string("You have failed for two days"),i);
}

///@param void, @brief simply calls evalute();
void manager::monitor()
{
    if(mylist.empty())
        std::cout<<"No employee to be monitored\n";
    else
        evaluate();
}

///@param void, @brief prints the progress results
void manager::show() const
{
    std::cout<<"\n\n";
    for(int j=0; j<30; j++)
        std::cout<<"--";
    std::cout<<"\nManager          : "<<name<<"  Salary:     "<<salary<<'\n';
    std::cout<<"Current active employees\n";

    size_t count=1;
    for(auto my_emply: mylist) {
        if(!my_emply.got_fired()&&!my_emply.to_be_fired()) {
            std::cout<<"\tNO "<<count<<" "<<my_emply.getname()<<"\tDays failed "<<my_emply.getdays()<<'\n';
            ++count;
        }
    }
    std::cout<<"\n\nBlacklisted emoployees\n";
    count=1;
    for(auto my_emp: mylist) {
        if(!my_emp.to_be_fired()&&!my_emp.got_fired()&&my_emp.blacklist()) {
            std::cout<<"\tNO "<<count<<" "<<my_emp.getname()<<"\tDays failed"<<my_emp.getdays()<<'\n';
            ++count;
        }
    }
    std::cout<<"\n\nFired employees\n";
    count=1;
    for(auto emp: mylist) {
        if(emp.got_fired()) {
            std::cout<<"\tNO "<<count<<" "<<emp.getname()<<"\tDays failed "<<emp.getdays()<<'\n';
            ++count;
        }
    }
}
#endif // MANAGER_H




int main()
{
    std::cout.sync_with_stdio(false);


    std::vector<Task> To_do {std::string("Accounting"),std::string("Customer care"),
                             std::string("Drafting")  ,std::string("IT support"),
                             std::string("Medical support"),std::string("Maintainance"),
                             std::string("Cleaning")  ,std::string("Write press")
                            };

    std::vector<employee> my_employees {employee("John",To_do),employee("Kylie",To_do),
                                        employee("Jeson",To_do),employee("Bobby",To_do),
                                        employee("Ashley",To_do),employee("kinsly",To_do),
                                        employee("labrinth",To_do),employee("medley",To_do),
                                        employee("Madison",To_do),employee("Mia",To_do),
                                        employee("Sydney",To_do),employee("Bailey",To_do)
                                       };


    manager mmajor("BIGMAN",4500.50,my_employees);


    for(int i=0; i<1000000; i++) {
        mmajor.monitor();
        //major.show();
    }
    mmajor.show();
}