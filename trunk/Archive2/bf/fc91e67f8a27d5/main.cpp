#include <iostream>
#include <iterator>


template<class T>
class range_object {
public:
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        T operator*() const { return cur_; }
        iterator& operator++() { cur_ += step_; return *this; }
        iterator& operator++(int) { iterator tmp(*this); cur_ += step_; return tmp; }

        bool operator==(const iterator& other) { return cur_ == other.cur_; }
        bool operator!=(const iterator& other) { return cur_ != other.cur_; }

    private:
        friend class range_object;

        iterator(T cur, T step) : cur_(cur), step_(step) { }

        T cur_;
        T step_;
    };

    range_object(T stop)
    : start_(0), stop_(stop), step_(1) { }

    range_object(T start, T stop)
    : start_(start), stop_(stop), step_(1) {
        if (stop_ < start_) start_ = stop_;
    }

    range_object(T start, T stop, T step)
    : start_(start), stop_(stop), step_(step) {
        if (step_ == 0) start_ = stop_;
        else if (step_ > 0) {
            if (stop_ < start_) start_ = stop_;

            auto size = stop_ - start_;
            stop_ = start_ + (1 + (size - 1) / step_) * step_;
        } else {
            if (start_ < stop_) start_ = stop_;

            auto size = start_ - stop_;
            stop_ = start_ - (1 + (size - 1) / -step_) * -step_;
        }
    }

    iterator begin() const {
        return {start_, step_};
    }

    iterator end() const {
        return {stop_, step_};
    }

private:
    T start_;
    T stop_;
    T step_;
};


template<class T>
range_object<T> range(T stop) { return {stop}; }

template<class T>
range_object<T> range(T start, T stop) { return {start, stop}; }

template<class T>
range_object<T> range(T start, T stop, T step) { return {start, stop, step}; }


int main(int argc, char** argv) {
    for (auto i : range(10)) std::cout << i << " ";
    std::cout << "\n";
    
    for (auto i : range(10, 20)) std::cout << i << " ";
    std::cout << "\n";
    
    
    for (auto i : range(9, -1, -1)) std::cout << i << " ";
    std::cout << "\n";
    
    for (auto i : range(0, 100, 4)) std::cout << i << " ";
    std::cout << "\n";
    
    return 0;
}
