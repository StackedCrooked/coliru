// -*- C++ Linked Lists -*-

#ifdef __TURBO_C  // Not sure about this
  #include <iostream.h> // cout
  #include <limits.h>   // INT_MIN
  #include <iomanip.h>  // setw
#else
  #include <iostream>
  #include <climits>
  #include <iomanip>
  using namespace std;
#endif

#define OK_       1
#define ERROR_    0
#define INSUFFICIENT_MEM INT_MIN        // Indicates insufficient memory
#define EMPTY_LIST       INT_MIN + 1    // Indicates empty list

// Forward List (singly-linked list)
class FList
{
    int*   ptr_;  // ughh
    size_t idx_;  // index
    size_t max_size_; // size

    int init_(size_t size) {
        // stdc++ throws bad_alloc instead
        if((ptr_ = new int[size]) == 0) {
            return ERROR_;
        }
        idx_ = 0;
        max_size_ = size;
        return OK_;
    }

public:
    FList(int size) { init_(size); } // constructor
    ~FList() { delete ptr_; }        // destructor

    int push(int n) {
        if(idx_ == max_size_) return INSUFFICIENT_MEM;
        ptr_[idx_++] = n;
        return OK_;
    }

    int pop() {
        if(idx_ == 0) return EMPTY_LIST;
        int ret = ptr_[idx_ - 1];
        --idx_;
        return ret;
    }

    int empty() { return idx_ == 0; }
    size_t size() { return idx_; }
    size_t max_size() { return max_size_; }

    int* begin() { return ptr_; }
    int* end() { return &ptr_[idx_]; }
};

int main()
{
    FList list(20);

    cout << left;
    
    // Fill the list
    for(int i = 0; i < 20; ++i) {
        int n = i * 10 + 20;
        list.push(i * 10 + 20);
        cout << setw(4) << n;
    }

    cout.put('\n');

    while(!list.empty()) {
        cout << setw(4) << list.pop();
    }

    cout.put('\n').flush();
}

