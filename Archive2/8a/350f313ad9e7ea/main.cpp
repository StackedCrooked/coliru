template<typename A, typename B>
class ISolutionToProblem
{
public:
    virtual void Init(const A & input, const B & param) = 0;
    virtual const B & ComputeSolution() = 0;

    virtual ~ISolutionToProblem() {}
};

template<typename T>
class MyAlgorithm:
    public ISolutionToProblem<void, T>
{
};

template<>
class MyAlgorithm:
    public ISolutionToProblem<typename MyAlgorithm<T>::WorkData, T>
{
public:
    struct WorkData { /* Stuff using T... */ };
    virtual void Init(const WorkData & input, const T & param);
    virtual const T & ComputeSolution();
};

int main() {
    MyAlgorithm<int> do_shit;
}