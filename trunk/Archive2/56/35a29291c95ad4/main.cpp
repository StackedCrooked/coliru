/* 
 * File:   main.cpp
 * Author: deszcz
 *
 * Created on October 22, 2014, 11:52 AM
 */

#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


using namespace std;

mutex m_is_writer;
int readers_num=0;
bool is_writer=false;
mutex m_cout;
mutex m_readers_num;

#define READERS_MAX



void reader(int i)
{
    m_is_writer.lock();
    m_readers_num.lock();
    readers_num++;
    m_cout.lock();
    cout << "Readers:" << readers_num << endl;
    m_cout.unlock();
    m_readers_num.unlock();
    m_is_writer.unlock();
    m_cout.lock();
    cout << "Reader " << i << " is reading" << endl;
    m_cout.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    m_readers_num.lock();
    readers_num--;
    m_cout.lock();
    cout << "Readers:" << readers_num << endl;
    m_cout.unlock();
    m_readers_num.unlock();
    m_cout.lock();
    cout << "Reader " << i << " went out" << endl;
    m_cout.unlock();
    
    

    

}

void writer()
{
    bool book_written = false;
    while (true) {
    m_is_writer.lock();
    while(!book_written)
    {
        book_written = false;
        m_readers_num.lock();
        if (readers_num == 0)
        {
            m_cout.lock();
            cout << "Writer is writing" << endl;
            m_cout.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            m_cout.lock();
            cout << "Writer went home" << endl;
            m_cout.unlock();
            book_written = true;
        }
        else
        {
            m_readers_num.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }
    m_is_writer.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
    
}




/*
 * 
 */
int main(int argc, char** argv) {
    
    vector<thread> vec;
    for (int i=0; i<10; i++)
         vec.push_back(thread(reader, i));
    thread t(writer);
    t.join();
     
    return 0;
}

