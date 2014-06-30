#include <iostream>
#include <string>
#include <boost/variant/variant.hpp>

struct A {
    A() : length() {}
    
    int length;
    std::string name;
};

struct B {
    B() : length() {}
    B(int l, const std::vector<unsigned> &v) : length(l), ages(v) {}
    B(const std::vector<unsigned> &v) : length(v.size()), ages(v) {}
    
    int length;
    std::vector<unsigned> ages;
};

struct C {
    std::string name;
    std::vector<unsigned> ages;
};


typedef boost::variant<A, B, C> Interface;
typedef std::vector<Interface> Container;

class PrinterVisitor : public boost::static_visitor<void> {
public:
    explicit PrinterVisitor(std::ostream &out) : out_(out), is_first_(true) {}
    
    void start() {
        out_ << "{ container: [";
        is_first_ = true;
    }
    
    void finish() const {
        if (!is_first_) out_ << "\n  ]\n}";
        else out_ << "]}";
        out_ << std::endl;
    }
        
    
    void operator ()(const A &a) {
        printDelim();
        
        out_ << "a: { length: " << a.length << ", name: \"" << a.name << "\" }";
    }
    
    void operator ()(const B &b) {
        printDelim();
        
        std::cout << "b: { length: " << b.length << ", ages: ";
        operator ()(b.ages);
        std::cout << " }";
    }
    
    void operator ()(const C &c) {
        printDelim();
        
        std::cout << "c: { name: \"" << c.name << "\", ages: ";
        operator ()(c.ages);
        std::cout << " }";
    }
    
    template <typename T>
    void operator ()(const std::vector<T> &ages) {
        typedef typename std::vector<T>::const_iterator iter;
        if (ages.empty())  
        {
            std::cout << "[]";
            return;
        }
        
        std::cout << "[";        
        for (iter first = ages.begin(), last = ages.begin() + ages.size() - 1; first != last; ++first) {
            std::cout << *first << ", ";
        }
        out_ << ages.back() << "]";
    }
protected:
    void printDelim() {
        if (is_first_) {
            is_first_ = false;
        } else {
            out_ << ",";
        }
        
        out_ << "\n    ";
    }
private:
    std::ostream &out_;
    bool is_first_;
};

int main() {
    Container myContainer;
    myContainer.push_back(A());
    myContainer.push_back(B({55, 67, 28, 33, 70}));
    myContainer.push_back(C());
    
    PrinterVisitor visitor(std::cout);
    visitor.start();
    for (Container::const_iterator first = myContainer.begin(), last = myContainer.end();
            first != last; ++first) {
        boost::apply_visitor(visitor, *first);
    }
    visitor.finish();
           
   return 0;
}
