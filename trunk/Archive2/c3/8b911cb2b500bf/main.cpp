#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>


    template<typename ... Args> struct SeriesBase;

    template<typename T>
    struct SeriesBase<T>
    {
        using ValueType = T;

        virtual ValueType operator()(int i) const = 0;
    };

    template<typename T, typename Derived>
    struct SeriesBase<T, Derived> : public SeriesBase<T>
    {
        using ValueType = typename SeriesBase<T>::ValueType;
        
        
        //removing the comment gives a compiler error ???
        // (if it weren't so, one could get rid of the template parameter "T"
        //
        //using ResultType = typename std::result_of<Derived(int)>::type;
        
        virtual ValueType operator()(int i) const override
        {
             return static_cast<Derived const&>(*this).operator()(i);
        }
    };


    template<typename T>
    struct Series : public SeriesBase<T, Series<T> >
    {
        using ValueType = typename SeriesBase<T>::ValueType;        
        Series() : store(10) { std::iota(store.begin(),store.end(),0); }
        
        //removing ValueType gives a compiler error ???        
        //        
        auto operator()(int i) const -> ValueType
        {
             return store[i];
        }
        std::vector<ValueType> store;
    };
    
    template<typename SeriesType>
    struct FirstTransformation : public SeriesBase<double, FirstTransformation<SeriesType> >
    {
        FirstTransformation(SeriesType const& _series) : series(_series) {}

        //How do I use a generic return value here (instead of "double") ???
        //
        auto operator()(int i) const -> double
        {
             return series(i)/11.1;
        }
        SeriesType const& series;
    };
    
    template<typename SeriesType>
    auto applyFirstTransformation(SeriesType const& series)
    {
        return FirstTransformation<SeriesType>(series);
    }


int main()
{
    Series<int> series;
    std::cout<<series(2)<<std::endl;
    
    std::cout<<applyFirstTransformation(series)(2)<<std::endl;
}
