#include <iostream>           // std::cout
#include <vector>
#include <map>
#include <utility>

class A {
    public:
    int a = 999;
    int b;
    unsigned c;
    void abc() { std::cout << "\n12314223\na = " << a << std::endl; }
    A() {std::cout << "CTOR\n";}
    ~A() { std::cout << "DTOR\n"; }
    void suicide() {delete this;}
};

class B {
    public:
    
    B(std::vector<A> vec): m_vec(vec) {
        
    }
    
    void printer() {
        if (m_vec.empty()) return;
        std::cout << "begin = " << m_vec.front().c << std::endl;
        std::cout << "end = " << m_vec.back().c << std::endl;
    }
    
    private:
    std::vector<A> m_vec;
    
};

void foo(double bar) {
    std::cout << "IM OK";
}

int bar(std::map<int, A*> &m_pipes) {
    int prev = 0;
    for (auto item : m_pipes) {
        if (item.first - prev > 1) return prev+1;
        prev = item.first;
    }
    return prev+1;
}

int main ()
{
    
    A* a = new A;
    std::cout << a << "\n";
    delete a;
    std::cout << a << "\n";
//    std::map<int, A*> m_pipes;
//    
//    for (int i = 10; i > 0; --i) {
//        if (i == 2 || i == 5) continue;
//          m_pipes[i] = new A();
//    }
//    
//    for (auto item : m_pipes) {
//        std::cout << item.first << " ";
//    }
//    std::cout << "\n";
//
//    
////    m_pipes.erase(result);
//    
//    std::cout << "result = " << bar(m_pipes) << "\n";
//    m_pipes[bar(m_pipes)] = new A();
//    
//    for (auto item : m_pipes) {
//        std::cout << item.first << " ";
//    }
//    std::cout << "\n";
//    
//    std::cout << "result = " << bar(m_pipes) << "\n";
//    m_pipes[bar(m_pipes)] = new A();
//    std::cout << "result = " << bar(m_pipes) << "\n";

//    for (auto item : m_pipes) {
//        std::cout << item.first << " ";
//    }
//    std::cout << "\n";

  return 0;
}