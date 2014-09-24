#include <boost/preprocessor.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>

#include <boost/fusion/container/vector/convert.hpp>

#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/join.hpp>

#include <boost/fusion/include/mpl.hpp>

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <boost/tuple/tuple.hpp>

#include <map>
#include <iostream>

namespace cvt
{

template<class T, class F>
struct conv;
    
template<class T>
struct conv<T,T>{
    T operator()(const T& s) { return s; }
};

template<> 
struct conv<int, std::string>{
    int operator()(const std::string& s)
    { return ::atoi(s.c_str()); }    
};

template<> 
struct conv<float, std::string>{
    float operator()(const std::string& s)
    { return ::atof(s.c_str()); }    
};

template<> 
struct conv<const char*, std::string>{
    const char* operator()(const std::string& s)
    { return s.c_str(); }    
};
}

template<typename V, typename T, int S, int E>
struct convert_all_impl;

/*
    End template recursion during conversion.
*/
template<typename V, typename T, int N>
struct convert_all_impl<V,T,N,N> {
    void operator()(const T&, V&) const {}
};

/*
    Fills V vector with converted values from T tuple.
*/
template<typename Args, typename Params, int N, int End>
struct convert_all_impl {

    //Convert from type. Used in function signature.
    typedef typename boost::fusion::result_of::value_at_c<Args, N> :: type to_type;
    
    //Convert to type. Passed argument type. Remove const and reference.
    typedef typename boost::tuples::element<N, Params> :: type raw_from_type;
    typedef typename boost::remove_const<
        typename boost::remove_reference< raw_from_type > :: type 
        > :: type non_const_ref_from_type;
    
    void operator()(const Params& t, Args& arguments) 
    {
        /*    
         Template-recursion filling 'arguments' vector with converted values from t.    
         It's replace previously default-constructed object by new one.
        
        TODO:
         * In case of using scoped_ptr instead of raw arguments types new need to allocate them on heap.
         * This could be done directly in ctv::conv specialization, but then all users should know about it. 
         * 
         * boost::fusion::at_c<N>(arguments) = cvt::conv<to_type, non_const_ref_from_type>()(boost::get<N>(t));
         * scoped_ptr<non_const_ref_from_type :: element_type> (
         *         cvt::conv< 
         *             to_type, 
         *             non_const_ref_from_type :: element_type;
         *         > ()( boost::get<N>(t) )
         * );
         * 
         * Used element_type is actual type stored in scoped_pr. We need this to construct(convert to) proper value
         * because cvt::conv is not specialized over scoped_ptr but over raw arguments types. In that case cnv should return pointer instead of object by value.
        */
        
        //Assing new values to already exsisted default constructed object.
        //I hope compiler will use copy-ellision to eliminae unnecesary copying.
        boost::fusion::at_c< N >( arguments ) = 
            ::cvt::conv< to_type, non_const_ref_from_type >()( boost::get< N >( t ) );
        
        //Convert next argument at index N+1, till we reach index End.
        convert_all_impl<Args, Params, N+1, End>()( t, arguments );
    }
};
    
/*
    Converts all elements(arguments) in tuple Params to apriopriate type from vector Args.
*/
template <typename Args>
struct converter{
    template<class Params>
    const Args& operator()(const Params& params)
    {    
        /* Call conversion on each element in vector. */
        convert_all_impl< Args, Params, 0, 
            boost::fusion::result_of::size<Args>::type::value >()(params, arguments_);
        
        /* Return vector filled with converted arguments */
        return arguments_;
    }
    
private:
    /*
     All actual arguments are stored in boost::fusion::vector.
     
      * TODO:
      * Each of those arguments need to be default constructable, to remove this we
      * need to use pointers instead of raw parameters types, but then we need to allocate all arguments on heap.
    */
    Args arguments_;
};

template<class R, class T, class Args> struct Functor;

/*
    This simulates variadic templates.
*/
#define _MAKE_FUNCTOR_TEMPLATE_(N)\
    template<class R, class T BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename A)>\
    struct Functor<R, T, boost::mpl::list<BOOST_PP_ENUM_PARAMS(N, A)> >{\
        typedef boost::function<R (T* BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, A))> type;\
    };
#define BOOST_PP_LOCAL_LIMITS (0, 10)
#define BOOST_PP_LOCAL_MACRO(n) _MAKE_FUNCTOR_TEMPLATE_(n)
#include BOOST_PP_LOCAL_ITERATE()
#undef _MAKE_FUNCTOR_TEMPLATE_

struct APIProvider; 

struct return_handler_base
{
    virtual void do_return(APIProvider*) = 0;
};

/*
    Base class for all ApiCalls.
*/
class BaseAPI {
public:    
    virtual return_handler_base* execute(const std::string& p0, const std::string& p1, const std::string& p2, const std::string& p3) = 0;
    virtual ~BaseAPI() {}
};

/*  
*/
template<class R, class T, class Args>
class ApiCall : public BaseAPI{
    typedef typename Functor<R, T, Args>::type functor_t;
public:    
    ApiCall(T* obj, functor_t func) 
        : execute_impl_( obj, func ) 
    {}
    
    return_handler_base* execute(const std::string& p0, const std::string& p1, const std::string& p2, const std::string& p3);

private:
    struct execute_impl_t {
    
        execute_impl_t(T* obj, functor_t func) 
            : _this( obj ), _func(func)  
        {}
    
        template<class Tuple>
        R operator()(const Tuple& params)
        {    
            /*
            * TODO:
            * template<class T>
            * struct add_scoped_ptr{
            *     typedef boost::scoped_ptr<
            *         typename boost::remove_referece<T> :: type 
            *     > type;
            * }
            * 
            * Above add_scoped_ptr trait can be used to transform all arguments types into appriopriate scoped_ptr type.
            */
             
            typedef typename 
                boost::mpl::transform< Args,
                    boost::remove_const<
                        boost::remove_reference< boost::mpl::_1 > :: type
                    > :: type
                > :: type no_const_ref_args;
                
            typedef typename 
                boost::fusion::result_of::as_vector< no_const_ref_args >::type type_vector_t;

            return boost::fusion::invoke(_func, 
                boost::fusion::join( boost::fusion::make_vector(_this), 
                    converter<type_vector_t>()(params)
                )
            );
        }
    private:
        T* _this;
        functor_t _func;
    };
    
private:
    execute_impl_t execute_impl_;
};

/*
    Variadic templates simulation.
    
    Creates make_api function with signature like below:
    ApiCall<R, T, boost::mpl::list<A1, AN> > make_api(T*, R(T::*)(A1...AN) );
    
    Where A1...AN are templates arguments from 1 to 10.
*/
#define _MAKE_MAKE_API_TEMPLATE_(N)\
    template <class R, class T BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, class A) >\
    ApiCall<R, T, boost::mpl::list<BOOST_PP_ENUM_PARAMS(N, A)> >*\
    make_api(T* _this, R (T::*_ptr)(BOOST_PP_ENUM_PARAMS(N, A))){\
        return new ApiCall<R, T, boost::mpl::list<BOOST_PP_ENUM_PARAMS(N, A)> >(_this, _ptr);\
    }
#define BOOST_PP_LOCAL_LIMITS (0, 10)
#define BOOST_PP_LOCAL_MACRO(n) _MAKE_MAKE_API_TEMPLATE_(n)
#include BOOST_PP_LOCAL_ITERATE()
#undef _MAKE_MAKE_API_TEMPLATE_

/*
    Holds all available api's
    Each API is function that can be called by particular name.
*/
struct APIProvider 
{
    typedef std::map<std::string, BaseAPI*> register_t;
    typedef register_t::iterator register_iterator;

protected:

    /*
        Register new api call.
        Each register api call can be called using execute function with appriopriate name and arguments list.
        
        _this: object on which we execute function. 
        func: function to execute on _this.
    */
    template<class T, class Func>
    void register_api(T* _this, std::string name, Func func)
    {
        /*
            This is using make_api with simulated variadic template to hold all possible function parameters
        */
        m_register[name] = make_api(_this, func);     
    }
    
public:

    /*
        Tries to find a registered function and call it with all passed arguments converted. 
    */
    virtual void execute(std::string& strReturn, const std::string& strCmd,
        const std::string& strParam1, const std::string& strParam2, 
        const std::string& strParam3, const std::string& strParam4)
    {
        register_iterator entry = m_register.find(strCmd);
        
        //if(entry == m_register.end())
        //    throw errors::no_such_command(strCmd);
            
        BaseAPI* api = entry->second;
        
        return_handler_base* ret = api->execute(strParam1, strParam2, strParam3, strParam4);
        
        //Handle return and invoke correct SEF function based on callee return type.
        ret->do_return(this);
    }
    
    /*
        Set return value to SEF.
    */
    void do_return(int iValue)                     { std::cout << "Return type int" << iValue << std::endl;     /*SET_RET_VAL_INT(iValue);*/            }
    void do_return(bool bValue)                    { std::cout << "Return type bool" << bValue << std::endl;    /*SET_RET_VAL_INT((int)bValue);*/        }
    void do_return(const char* szValue)            { std::cout << "Return type const char*" << szValue << std::endl;    /*SET_RET_VAL_ASCII(szValue);*/            }
    void do_return(const std::string& strValue)    { std::cout << "Return type std::string" << strValue << std::endl;/*SET_RET_VAL_ASCII(strValue.c_str());*/}
    
private:
    std::map<std::string, BaseAPI*> m_register;
};

/*
    Handle return value. 
*/
template<class T, class ReturnType>
struct return_handler
    : public return_handler_base
{    
    typedef boost::function<ReturnType()> callable_t; 
    
    return_handler(boost::function<ReturnType()> f)
        : _callable(f) 
    {}

    /*
        do_return
    */        
    void do_return(APIProvider* callee)
    {
        /*
            Decide which function to select based on callable return type.
            Callable is non-parameter function made from registered function by binding all arguments to parameters.
        */
        callee->do_return(_callable());
    }
    
private:
    callable_t _callable;
};

/*
    Specialization to handle not returning any value.
*/
template<class T>
struct return_handler<T, void>
    : public return_handler_base
{    
    typedef boost::function<void()> callable_t; 
    
    return_handler(boost::function<void()> f)
        : _callable(f) {}
    
    void do_return(APIProvider* callee)
    {
        /*
         Just call function without any returning value.
        */
        _callable();
    }
    
private:
    callable_t _callable;
};

template<class R, class T, class Args>
return_handler_base* ApiCall<R, T, Args>::
execute(const std::string& param_0, const std::string& param_1, const std::string& param_2, const std::string& param_3)
{
    /*
        Handle return value from callee.
        For now T is ignored.
    */
    return new return_handler<T, R>
    (
        /*
            Bind all actual arguments to parameters to create non-parameter callable.
            Binds is done by reference so no copy is involved.
        */
        boost::bind<R>
        (
            execute_impl_, 
            boost::make_tuple
            (
                boost::cref(param_0), 
                boost::cref(param_1), 
                boost::cref(param_2), 
                boost::cref(param_3)
            )
        )
    );
}
    
/*template<class R, class T, class Args>
return_handler_base* ApiCall<R, T, Args>::
execute(std::string& p0, std::string& p1, std::string& p2, std::string& p3, std::string& p4, 
        std::string& p5, std::string& p6, std::string& p7, std::string& p8, std::string& p9)
{
    return new return_handler<T, R>
    (
        boost::bind<R>
        (
            execute_impl_, 
            boost::make_tuple(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)
        )
    );
}*/

struct TVScanTask
{
    std::string InitChannelScan(int type){return "";}
    int PauseChannelScan(){return 10;}
    void ResumeChannelScan(){return;}
    bool StopChannelScan(){return false;}
    bool StartChannelScan(const char* json){return false;}    
    bool Test1(int, int, int, float){return false;}
};

class CEmpEngineBase 
    : public APIProvider
{
};

class TVScanEngine 
        : public CEmpEngineBase
{
public:
    TVScanEngine()
    {    
        TVScanTask* task = new TVScanTask();
        
        register_api(task, "InitChannelScan", &TVScanTask::InitChannelScan);
        register_api(task, "PauseChannelScan", &TVScanTask::PauseChannelScan);
        register_api(task, "ResumeChannelScan", &TVScanTask::ResumeChannelScan);
        register_api(task, "StopChannelScan", &TVScanTask::StopChannelScan);
        register_api(task, "StartChannelScan", &TVScanTask::StartChannelScan);
        register_api(task, "Test1", &TVScanTask::Test1);
    }
};

int main()
{        
    std::string ret;
    
    TVScanEngine engine;    
    engine.execute(ret, "InitChannelScan", "1", "2", "3", "4");
    engine.execute(ret, "PauseChannelScan", "", "", "", "");
    engine.execute(ret, "Test1", "1", "2", "3", "4");
    engine.execute(ret, "StartChannelScan", "1", "2", "3", "4.0");
    return 0;
}