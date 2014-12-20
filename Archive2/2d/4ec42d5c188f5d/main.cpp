#include <limits>


//! Minimum is a convenience utility for keeping track of the minimum value set.
template<typename T>
struct Minimum
{
    Minimum(const T& inInitialValue = std::numeric_limits<T>::max()) : value_(inInitialValue) { }

    T operator=(const T& value)
    {
        if (value < value_) { value_ = value; }
        return value;
    }

    // We return T() if still "unset".
    operator T() const { return value_ == std::numeric_limits<T>::max() ? T() : value_; }

private:
    T value_;
};

//! Maximum is a convenience utility for keeping track of the maximum value set.
template<typename T>
struct Maximum
{
    Maximum(T initial_value = std::numeric_limits<T>::min()) : value_(initial_value) { }

    T operator=(const T& value)
    {
        if (value > value_) { value_ = value; }
        return value;
    }

    // We return T() if still "unset".
    operator T() const { return value_ == std::numeric_limits<T>::min() ? T() : value_; }

private:
    T value_;
};


//! Current is a simple value wrapper that is probably only meaningful
//! when used together with Minimum<T> and Maximum<T>
template<typename T>
struct Current
{
    Current(T initial_value = T()) : value_(initial_value) {}
    T operator=(const T& value) { value_ = value; return value; }
    operator T() const { return value_; }

private:
    T value_;
};


//! MinMaxCur combines Minimum<T>, Maximum<T> and Current<T>.
template<typename T>
struct MinMaxCur
{
    MinMaxCur() : mMinimum(), mMaximum(), mCurrent() {}

    // Allow user to explicitly specify initial values
    explicit MinMaxCur(const T& inMinimum, const T& inMaximum, const T& inCurrent) : mMinimum(inMinimum), mMaximum(inMaximum), mCurrent(inCurrent) { }

    T operator=(const T& value)
    {
        mMinimum = value;
        mMaximum = value;
        mCurrent = value;
        return value;
    }

    T minimum() const { return mMinimum; }
    T maximum() const { return mMaximum; }
    T current() const { return mCurrent; }

private:
    Minimum<T> mMinimum;
    Maximum<T> mMaximum;
    Current<T> mCurrent;
};


#include <iostream>


int main()
{
    MinMaxCur<int> temperature_tracker;
    temperature_tracker = 7;
    temperature_tracker = 2;
    temperature_tracker = 4;
    temperature_tracker = -1;
    temperature_tracker = 3;
    temperature_tracker = 4;
    temperature_tracker = 9;
    temperature_tracker = 5;
    
    std::cout
        << "min=" << temperature_tracker.minimum() << " " 
        << "cur=" << temperature_tracker.current() << " " 
        << "max=" << temperature_tracker.maximum() << std::endl;
}