#include <iostream>
#include <string>
#include <map>

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << '[';
    for (auto& e : m) {
        os << e.first << ", " << e.second << "; ";
    }
    os << ']';

    return os;
}

struct Count {
    long count;

    Count(const long& initCount = 0) : count(initCount) {};

    friend std::ostream& operator<<(std::ostream& os, const Count& c);
    
    const Count operator+(const Count& other) const {
        return Count(this->count + other.count);
    };
    
    Count& operator+=(const Count& other) {
        this->count += other.count;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const Count& c) {
    os << "[Count: " << c.count << "]";
    return os;
}

typedef std::map<std::string, Count> CounterMap;

struct CounterHolder {
    CounterMap mappedNumbers;

    CounterHolder() : mappedNumbers() {
        mappedNumbers.insert(CounterMap::value_type("abc", 123));
        mappedNumbers.insert(CounterMap::value_type("def", 456));
        mappedNumbers.insert(CounterMap::value_type("ghi", 789));
    }
    
    Count& getCounter(const std::string& key, const long initialValue = 0) {
        // Instantiate a new value to insert
        CounterMap::value_type newValue(key, Count(initialValue));
        // Attempt to insert it, and get the result
        std::pair<CounterMap::iterator, bool> result = mappedNumbers.insert(newValue);
        // Return the value from the iterator, whether or not it failed
        return (result.first)->second;
    }
};

void testMap() {
    CounterHolder counterHolder;
    std::cout << "Before adding to map:\n\t" << counterHolder.mappedNumbers << std::endl;

    Count& result1 = counterHolder.getCounter("jkl");
    std::cout << "After one call to:\n\tgetCounter(\"jkl\") = " << result1 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
    
    Count& result2 = counterHolder.getCounter("abc");
    std::cout << "After one call to:\n\tgetCounter(\"abc\") = " << result2 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
    
    Count& result3 = counterHolder.getCounter("def", 123456789);
    std::cout << "After one call to:\n\tgetCounter(\"def\", 123456789) = " << result3 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
    
    Count newResult = result1 + result2 + result3;
    std::cout << "After replacing value " << result3 << " from key \"def\" with value " << newResult << ":\n\t";
    result3 = newResult;
    std::cout << counterHolder.mappedNumbers << std::endl;
    
    Count& result4 = counterHolder.getCounter("xyz", 123456789);
    std::cout << "After one call to:\n\tgetCounter(\"xyz\", 123456789) = " << result4 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
    
    Count& result5 = counterHolder.getCounter("abc");
    std::cout << "After one call to:\n\tgetCounter(\"abc\") = " << result5 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
    Count result5Copy = result5;
    result5 += 9876543210;
    std::cout << "After `operator += 9876543210` on " << result5Copy << " = " << result5 << ":\n\t" << counterHolder.mappedNumbers << std::endl;
}

int main()
{
    testMap();
}
