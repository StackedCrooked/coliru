    #include <iostream>
    #include <iomanip>

    class fmt_longptr {
    public:
        fmt_longptr(void* ptr) : ptr_(ptr) {}
        void put(std::ostream& os) const {
            os << "0x" << std::hex << std::setw(2 * sizeof(void*)) << std::setfill('0') << (unsigned long)ptr_;
        }
    private:
        friend std::ostream& operator<<(std::ostream& os, const fmt_longptr& fmt);
        void* ptr_;
    };

    std::ostream& operator<<(std::ostream& os, const fmt_longptr& fmt) {
        fmt.put(os);
        return os;
    }

    int main() {
        int a;
    
        std::cout << std::setfill('0') << std::setw(2 * sizeof(void*)) << &a << std::endl;
        std::cout << fmt_longptr(&a) << std::endl;
	    return 0;
    }