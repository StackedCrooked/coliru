#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
 
struct Employee {
    Employee(int id) : id(id) {}
    int id;
    std::vector<int> lunch_partners;
    std::mutex m;
};
 
void send_mail(Employee &e1, Employee &e2)
{
    // simulate a time-consuming messaging operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
void assign_lunch_partner(Employee &e1, Employee &e2)
{
    // use std::lock to acquire two locks without worrying about 
    // other calls to assign_lunch_partner deadlocking us
    std::lock(e1.m, e2.m);
 
    e1.lunch_partners.push_back(e2.id);
    e2.lunch_partners.push_back(e1.id);
 
    e1.m.unlock();
    e2.m.unlock();
 
    send_mail(e1, e2);
    send_mail(e2, e1);
}
 
int main()
{
    Employee alice(0), bob(1), christina(2), dave(3);
 
    // assign in parallel threads because mailing users about lunch assignments
    // takes a long time
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));
 
    for (auto &thread : threads) thread.join();
}