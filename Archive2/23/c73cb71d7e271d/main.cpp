#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
 
struct Employee {
    Employee(std::string id) : id(id) {}
    std::string id;
    std::vector<std::string> lunch_partners;
    std::mutex m;
    std::string output() const
    {
        std::string ret("Employee ");
        ret += id;
        ret += " has lunch partners: ";
        for( const auto& partner : lunch_partners ) {
            ret += partner;
            ret += " ";
        }
        return ret;
    }
};
 
void send_mail(Employee &, Employee &)
{
    // simulate a time-consuming messaging operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
void assign_lunch_partner(Employee &e1, Employee &e2)
{
    std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
    // use std::lock to acquire two locks without worrying about 
    // other calls to assign_lunch_partner deadlocking us
    std::lock(e1.m, e2.m);

    std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;

    e1.lunch_partners.push_back(e2.id);
    e2.lunch_partners.push_back(e1.id);
 
    e1.m.unlock();
    e2.m.unlock();
 
    send_mail(e1, e2);
    send_mail(e2, e1);
}
 
int main()
{
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");
 
    // assign in parallel threads because mailing users about lunch assignments
    // takes a long time
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));
 
    for (auto &thread : threads) thread.join();
 
    std::cout << alice.output() << std::endl;
    std::cout << bob.output() << std::endl;
    std::cout << christina.output() << std::endl;
    std::cout << dave.output() << std::endl;
}