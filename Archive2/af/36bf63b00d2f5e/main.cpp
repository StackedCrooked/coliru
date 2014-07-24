#include <string>
typedef long HRESULT;

struct IAccessor 
{
    HRESULT AddRefAccessor( std::string, int * );
};

IAccessor *m_wrapped;

namespace Impl
{
enum ParameterType
{
POINTER_PARAMETER,
ARRAY_PARAMETER
};


template <typename WrappedType, ParameterType ParamType, bool IsOutputParameter>
   struct WrappedParameter // Definition left out for brevity
    {
        WrappedParameter(int *){}
        operator int *() const { return nullptr; }
        int *GetWrapped() const { return nullptr; }
    };

template <typename T>
struct ParameterUnwrapper
{
    static T UnwrapParameter(const T& in_param)
    {
        return in_param;
    }
};

template <typename T, ParameterType ParamType, bool IsOutputParameter>
struct ParameterUnwrapper<WrappedParameter<T, ParamType, IsOutputParameter>>
{
    static T UnwrapParameter(const WrappedParameter<T, ParamType, IsOutputParameter>& in_param)
    {
        return in_param.GetWrapped();
    }
};

template <typename T>
T UnwrapParameter(T in_param)
{
    return Impl::ParameterUnwrapper<T>::UnwrapParameter(in_param);
}

template <typename T>
Impl::WrappedParameter<T, Impl::POINTER_PARAMETER, true> WrapOutputPointerParameter(T in_param)
{
    return Impl::WrappedParameter<T, Impl::POINTER_PARAMETER, true>(in_param);
}

template <typename MemFunc, typename ...Args>
HRESULT ExecuteAndLog(
    MemFunc in_memberFunction,
    const std::string& in_methodName,
    Args... args) //-> decltype((m_wrapped->*in_memberFunction)(UnwrapParameter(args)...))
{
    
//    return ExecuteFunctorAndLog(
  //      [&]() 
  { return (m_wrapped->*in_memberFunction)(UnwrapParameter(args)...); }//,
        //in_methodName,
        //args...);
}

}

    HRESULT IAccessor::AddRefAccessor( std::string hAccessor, int *pcRefCount )
    {
    return ExecuteAndLog(
        &IAccessor::AddRefAccessor,
        "AddRefAccessor",
        hAccessor,
        Impl::WrapOutputPointerParameter(pcRefCount));
    }

int main()
{
}

