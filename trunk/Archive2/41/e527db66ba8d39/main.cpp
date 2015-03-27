#include<iostream>
#include<typeinfo>
#include<memory>

    template<typename ... Args> struct VectorBase;

    template<typename T>
    struct VectorBase<T>
    {
         virtual T eval(int) const = 0;
         auto operator[](int i) {return this->eval(i);}
    };

    template<typename T, typename Derived>
    struct VectorBase<T, Derived> : public VectorBase<T>
    {
         virtual T eval(int i) const override final { return this->operator[](i); }
         auto operator[](int i) const
         {
              return static_cast<Derived const&>(*this).operator[](i);
         }
    };

    template<typename T>
    struct Vector : public VectorBase<T, Vector<T> >
    {
         //just for code shortness,
         //in reality there is a container which returns the corresponding elements
         auto operator[](int i) const { return T(); }
    };

    namespace detail
    {
        template<typename T, typename VectorType>
        struct SomeTransformation : public VectorBase<T, SomeTransformation<T, VectorType> >
        {
             VectorType const& v;
             SomeTransformation(VectorType const& _v) : v(_v) {}
             auto operator[](int i) const
             {
                  //do something with vector v and return i-th element, e.g.
                  return v[i]*0.1;
             }
        };
    }

    struct DummyType
    {
         //make any type convertible to DummyType
         template<typename T> DummyType(T const&) {}
    };
    
    template<typename VectorType>
    using SomeTransformationValueType = decltype(std::declval<detail::SomeTransformation<DummyType, VectorType> >().operator[](0));

    template<typename VectorType>
    using SomeTransformation = typename detail::SomeTransformation<SomeTransformationValueType<VectorType>, VectorType>;
    
    
    int main()
    {
        Vector<int> v;
        std::cout<<typeid(decltype(v[0])).name()<<std::endl;  //prints "i" for int        

        auto u = SomeTransformation<decltype(v)>(v);
        std::cout<<typeid(decltype(u[0])).name()<<std::endl;  //prints "d" for double        

        std::unique_ptr<VectorBase<double> > ud = std::make_unique<SomeTransformation<decltype(v)> >(v);  //works
        //std::unique_ptr<VectorBase<int> > ud = std::make_unique<SomeTransformation<decltype(v)> >(v);     //gives a compile-time error, which is good
    }
    