#include <iostream>

// ===============================================
// GENERIC FRAMEWORK
// ===============================================

template<class... > struct overloaded;

template<class F1, class... Fs>
struct overloaded<F1, Fs...> : F1, overloaded<Fs...>::type
{
    typedef overloaded type;

    overloaded(F1 head, Fs... tail)
        : F1(head)
        , overloaded<Fs...>::type(tail...) { }

    using F1::operator();
    using F1::operator = ;
    using overloaded<Fs...>::type::operator();
    using overloaded<Fs...>::type::operator =;
};

template<class F>
struct overloaded<F> : F
{
    typedef F type;
    using F::operator();
    using F::operator =;
};

template<class... Fs>
typename overloaded<Fs...>::type overload(Fs... os)
{ return overloaded<Fs...>(os...); }

// ===============================================
// MOTION-SPECIFIC FRAMEWORK
// ===============================================

template<class... Fs>
auto motion_handler(Fs... os)
{ return overload(os..., [] (auto error) { throw error; }); }

enum HRESULT
{
    hardware_error,
    tracking_error,
    timeout_error,
    // ...
};

#include <stdexcept>

template<HRESULT error> 
struct motion_error : std::exception { };

using hardware_exception = motion_error<hardware_error>;
using tracking_exception = motion_error<tracking_error>;
struct timeout_exception : motion_error<timeout_error> { timeout_exception(int) { } };

template<typename F>
void handle_motion_error(HRESULT error, F&& handler)
{
    switch (error)
    {
        case timeout_error: handler(motion_error<timeout_error>{}); break;
        case hardware_error: handler(motion_error<hardware_error>{}); break;
        case tracking_error: handler(motion_error<tracking_error>{}); break;
        default: break;
    }
}

template<typename F>
void throw_and_show(F&& f)
{
    try
    {
        f();
    }
    catch (timeout_exception const&)
    {
        std::cout << "Thrown timeout error" << std::endl;
    }
    catch (hardware_exception const&)
    {
        std::cout << "Thrown hardware error" << std::endl;
    }
    catch (tracking_exception const&)
    {
        std::cout << "Thrown tracking error" << std::endl;
    }
    catch (std::exception const&)
    {
        std::cout << "Thrown generic error" << std::endl;
    }    
}

int main()
{
    auto timeout = 42;
    
    auto f = motion_handler([&] (motion_error<timeout_error>) { throw timeout_exception(timeout); });
    
    throw_and_show([&] { handle_motion_error(timeout_error, f); });
    throw_and_show([&] { handle_motion_error(hardware_exception, f); });
}
