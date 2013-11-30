#include <iostream>
#include <type_traits>
#include <string>

class Algorithm {
public:
    struct WorkData;
    virtual void Compute(WorkData) = 0;
    
    virtual ~Algorithm();
};

class Do_Something :
    public Algorithm {
public:
    struct WorkData {
        int A;
        int B;
        int C;
    };
    
    void Compute(WorkData workData) {
        std::cout << workData.A + workData.B + workData.C << std::endl;
    }
};

template <typename T>
class AlgorithmManager
    : public Algorithm {
public:
    AlgorithmManager() { }
    ~AlgorithmManager() { }

    virtual void Compute(typename T::WorkData workData) {
        T::Compute();
    }
};

int main ()
{
    AlgorithmManager<Do_Something>();
    return 0;
}
                                                        