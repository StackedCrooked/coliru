#include <string>
typedef long HRESULT;

struct IAccessor *m_wrapped;

namespace Impl
{
enum ParameterType
{
POINTER_PARAMETER,
ARRAY_PARAMETER
};


template <typename WrappedType, ParameterType ParamType, bool IsOutputParameter>
    class WrappedParameter; // Definition left out for brevity

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
    return ExecuteFunctorAndLog(
        [&]() { return (m_wrapped->*in_memberFunction)(UnwrapParameter(args)...); },
        in_methodName,
        args...);
}

}

int main()
{
}

