#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <iostream>

struct MyColumnType { 
    
    class MyColumnElementValue {
        double a_;
        std::string b_;
        int c_;
    public:
        double& a() {return a_;}
        const double& a() const {return a_;}
        std::string& b() {return b_;}
        const std::string& b() const {return b_;}
        int& c() {return c_;}
        const int& c() const {return c_;}
                
        friend void swap(MyColumnElementValue& lhs, MyColumnElementValue& rhs) { 
            std::swap(lhs.a_, rhs.a_);
            lhs.b_.swap(rhs.b_);
            std::swap(lhs.c_, rhs.c_);
        }  
    };
    
    class MyColumnElementReference {
        MyColumnType* parent_;
        int index_;
    public:
        MyColumnElementReference() : parent_(), index_()  {}
        MyColumnElementReference(MyColumnType* parent, int index) : parent_(parent), index_(index) {}
        MyColumnElementReference& operator=(MyColumnElementReference rhs) {
            parent_->a[index_] = rhs.a();
            parent_->b[index_] = std::move(rhs.b());
            parent_->c[index_] = rhs.c();
            return *this;
        }
        MyColumnElementReference& operator=(MyColumnElementValue rhs) {
            parent_->a[index_] = rhs.a();
            parent_->b[index_] = std::move(rhs.b());
            parent_->c[index_] = rhs.c();
            return *this;
        }
        operator MyColumnElementValue() const {
            MyColumnElementValue ret;
            ret.a() = a();
            ret.b() = b();
            ret.c() = c();
            return ret;
        }
        
        double& a() {return parent_->a[index_];}
        const double& a() const {return parent_->a[index_];}
        std::string& b() {return parent_->b[index_];}
        const std::string& b() const {return parent_->b[index_];}
        int& c() {return parent_->c[index_];}
        const int& c() const {return parent_->c[index_];}
                
        friend void swap(MyColumnElementReference lhs, MyColumnElementReference rhs) { 
            std::cout << "swapping " << lhs.index_ << " and " << rhs.index_ << "\n";
            std::swap(lhs.a(), rhs.a());
            lhs.b().swap(rhs.b());
            std::swap(lhs.c(), rhs.c());
        }  
        friend void swap(MyColumnElementReference lhs, MyColumnElementValue& rhs) { 
            std::cout << "swapping " << lhs.index_ << " and value\n";
            std::swap(lhs.a(), rhs.a());
            lhs.b().swap(rhs.b());
            std::swap(lhs.c(), rhs.c());
        }  
        friend void swap(MyColumnElementValue& lhs, MyColumnElementReference rhs) { 
            std::cout << "swapping value and " << rhs.index_ << "\n";
            std::swap(lhs.a(), rhs.a());
            lhs.b().swap(rhs.b());
            std::swap(lhs.c(), rhs.c());
        }  
    };
    
    class MyColumnIterator {     
        MyColumnType* parent_;
        int index_;
    public:
        typedef int difference_type;
        typedef int size_type;
        typedef MyColumnElementValue value_type;
        typedef MyColumnElementReference reference;
        typedef MyColumnElementReference pointer;
        typedef std::random_access_iterator_tag iterator_category;
        
        MyColumnIterator() : parent_(), index_()  {}
        MyColumnIterator(MyColumnType* parent, int index) : parent_(parent), index_(index) {}
        
        friend bool operator==(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_==rhs.index_;}
        friend bool operator!=(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_!=rhs.index_;}
        friend bool operator<(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_<rhs.index_;}
        friend bool operator>(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_>rhs.index_;}
        friend bool operator<=(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_<=rhs.index_;}
        friend bool operator>=(const MyColumnIterator& lhs, const MyColumnIterator& rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_>=rhs.index_;} 
        
        MyColumnIterator& operator++() {++index_; return *this;}
        MyColumnIterator operator++(int) {return MyColumnIterator(parent_, index_++);}
        MyColumnIterator& operator+=(size_type o) {index_+=o; return *this;}
        friend MyColumnIterator operator+(MyColumnIterator it, size_type o) {return it+=o;}
        friend MyColumnIterator operator+(size_type o, MyColumnIterator it) {return it+=o;}
        MyColumnIterator& operator--() {--index_; return *this;}
        MyColumnIterator operator--(int) {return MyColumnIterator(parent_, index_--);}
        MyColumnIterator& operator-=(size_type o) {index_-=o; return *this;} 
        friend MyColumnIterator operator-(MyColumnIterator it, size_type o) {return it-=o;}
        friend difference_type operator-(MyColumnIterator lhs, MyColumnIterator rhs) {assert(lhs.parent_==rhs.parent_); return lhs.index_-rhs.index_;}
        
        MyColumnElementReference operator*() const {return MyColumnElementReference(parent_, index_);}
        MyColumnElementReference operator->() const {return MyColumnElementReference(parent_, index_);}
        MyColumnElementReference operator[](size_type o) const {return MyColumnElementReference(parent_, index_+o);}
        
        friend void swap(MyColumnIterator& lhs, MyColumnIterator& rhs) {std::swap(lhs.parent_, rhs.parent_);std::swap(lhs.index_, rhs.index_);}  
    };

  // Data: Each row represents a member of an object.
  std::vector<double> a;   // All vectors are guaranteed to have always
  std::vector<std::string> b;   // the same length.
  std::vector<int> c;

  void copy(int from_pos, int to_pos); // The column type provides an interface
  void swap(int pos_a, int pos_b);     // for copying, swapping, ...

  void push_back(double a_, std::string b_, int c_) {a.push_back(a_); b.emplace_back(std::move(b_)); c.push_back(c_);}
  void pop_back() {}
  void insert(int pos) {}
  void remove(int pos) {}
  // The interface can be extended/modified if required
  
  MyColumnIterator begin() {return MyColumnIterator(this, 0);}
  MyColumnIterator end() {return MyColumnIterator(this, a.size());}
};

bool predicate(const MyColumnType::MyColumnElementValue& lhs, const MyColumnType::MyColumnElementValue& rhs) 
{
    std::cout << "comparing " << lhs.a() << " and " << rhs.a() << "\n";
    return lhs.a()<rhs.a();
}

int main() {
    MyColumnType data;
    data.push_back(5.0, "HI", -1);
	data.push_back(3.0, "WORLD", 0);
    std::sort(data.begin(), data.end(), predicate);
    std::cout << data.a[0] << ' ' << data.a[1] << '\n';
    std::cout << data.b[0] << ' ' << data.b[1] << '\n';
    std::cout << data.c[0] << ' ' << data.c[1] << '\n';

	return 0;
}
