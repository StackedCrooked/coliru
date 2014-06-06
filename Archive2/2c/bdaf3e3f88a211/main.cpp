#include<iostream>

#include<chrono>

#include<vector>

#include<list>

#include<algorithm>

 

using namespace std;

using namespace std::chrono;

 

template<class Algorithm>

struct PerformanceChecker

{

    Algorithm m_algorithm {};

    nanoseconds m_nanos {};

    

    void executeCheck()

    {

        using namespace std::chrono;

        const auto startTime = steady_clock::now();

        m_algorithm.execute();

        const auto endTime = steady_clock::now();

        m_nanos= duration_cast<nanoseconds>(endTime - startTime);

    }    

    

    nanoseconds getNanos()

    {

        return m_nanos;

    }

    

};

 

template <class STLContainer>

struct TestBase {

    static const int Length = 10000;

    STLContainer m_Container {};

    

    TestBase()     {

        for(int i=0; i<Length; ++i)

        {

            m_Container.push_back(42);

        }

    }

};

 

template <class STLContainer>

struct ForLoopIteratorSumUpTest

          : public TestBase<STLContainer>

{

    void execute()

    {

        volatile long long sum=0;

        for( auto iter = TestBase<STLContainer>::m_Container.begin(); iter != TestBase<STLContainer>::m_Container.end(); ++iter)

        {

            sum += *iter;

        }

    }

};

 

template <class STLContainer>

struct RangeForLoopIteratorSumUpTest

          : public TestBase<STLContainer>

{

    void execute()

    {

        volatile long long sum=0;

        for( auto elem : TestBase<STLContainer>::m_Container)

        {

            sum += elem;

        }

    }

};

 

template <class STLContainer>

struct ForeachSumUpTest

          : public TestBase<STLContainer>

{

    void execute()

    {

        volatile long long sum=0;

        for_each( this->m_Container.begin(), TestBase<STLContainer>::m_Container.end(),[&] (typename STLContainer::const_reference elem) {sum += elem;} );

    }

};


int main() {

    

        using Container = vector<int>;      

    

        PerformanceChecker<ForLoopIteratorSumUpTest<Container>> performanceChecker_For;

        performanceChecker_For.executeCheck();

        std::cout << "ForLoopIteratorSumUpTest<list>: " <<  performanceChecker_For.getNanos().count() << " ns"  << std::endl;

        

        PerformanceChecker<RangeForLoopIteratorSumUpTest<Container>> performanceChecker_RangeFor;

        performanceChecker_RangeFor.executeCheck();

        std::cout << "RangeForLoopIteratorSumUpTest<list>: " <<  performanceChecker_RangeFor.getNanos().count() << " ns"  << std::endl;

        

        PerformanceChecker<ForeachSumUpTest<Container>> performanceChecker_Foreach;

        performanceChecker_Foreach.executeCheck();

        std::cout << "ForeachSumUpTest<list>: " <<  performanceChecker_Foreach.getNanos().count() << " ns"  << std::endl;

}

 

