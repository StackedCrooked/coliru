#ifndef STACKED_RPC_CLIENT_H
#define STACKED_RPC_CLIENT_H


#include "Stacked/RPC/Utilities.h"
#include "Stacked/RPC/ResultCode.h"
#include "Stacked/RPC/Serialization.h"
#include "Stacked/RPC/Exception.h"
#include <boost/scoped_ptr.hpp>
#include <memory>
#include <string>
#include <stdexcept>
#include <tuple>
#include <stdint.h>


namespace Stacked {
namespace RPC {


/**
 * The Client class is used for connecting to an RPC server and sending
 * RPC commands.
 */
class Client
{
public:
    struct ConnectionError : Exception
    {
        ConnectionError(const std::string& host, int port) :
            Exception(host + ":" + std::to_string(port))
        {
            appendName("ConnectionError");
        }
    };

    struct BadResultCode : Exception
    {
        BadResultCode(ResultCode result_code) : Exception(static_cast<uint32_t>(result_code))
        {
            appendName("BadResultCode");
        }
    };

    Client(const std::string & host, uint16_t port);

    ~Client();

    typedef std::function<void(const Exception&)> ExceptionHandler;

    //! Setting an exception handler allows you to intercept all exceptions
    //! in one central place. This enables you to rethrow them as a different
    //! type.
    void setExceptionHandler(const ExceptionHandler& inExceptionHandler);


    /**
     * Blocking RPC call for commands with signature `result_type(arguments...)`.
     * Exceptions that occur remotely will be rethrown.
     *
     * Usage example:
     *   int sum = client.send<Sum>(3, 4);
     */
    template<typename C, typename ...Args>
    typename C::result_type send(Args&& ...args) const // is an rpc call const? anyway this enables const methods to retrieve info over rpc
    {
        typedef typename C::argument_type A;
        return const_cast<Client&>(*this).do_send<C>(A(std::forward<Args>(args)...), Detail::ResultTypeTag<C>());
    }

private:

    //! For commands with signature: void(void)
    template<typename C>
    void do_send(Detail::ResultTypeIsVoid<true>)
    {
        try_deserialize_result<void>(sendImpl(GetTypeName(Identity<C>()), ""));
    }

    //! For commands with signature: result_type(void)
    template<typename C>
    typename C::result_type do_send(Detail::ResultTypeIsVoid<false>)
    {
        return try_deserialize_result<typename C::result_type>(sendImpl(GetTypeName(Identity<C>()), ""));
    }

    //! For commands with signature: void(argument_type)
    template<typename C>
    void do_send(typename C::argument_type arg, Detail::ResultTypeIsVoid<true>)
    {
        try_deserialize_result<void>(sendImpl(GetTypeName(Identity<C>()), Serialize(arg)));
    }

    //! For commands with signature: result_type(argument_type)
    template<typename C>
    typename C::result_type do_send(typename C::argument_type arg, Detail::ResultTypeIsVoid<false>)
    {
        return try_deserialize_result<typename C::result_type>(sendImpl(GetTypeName(Identity<C>()), Serialize(arg)));
    }

    template<typename R>
    R try_deserialize_result(const std::string & maybe)
    {
        auto result = Deserialize<std::tuple<int32_t, std::string>>(maybe);
        auto result_code = static_cast<ResultCode>(std::get<0>(result));
        switch (result_code)
        {
            case ResultCode::Success:
            {
                return deserialize_result<R>(std::get<1>(result), Detail::ResultTypeTag<R>());
            }
            case ResultCode::Failure:
            {
                try
                {
                    throw Deserialize<Exception>(std::get<1>(result));
                }
                catch (Exception& exc)
                {
                    handle_error(exc);
                    throw exc;
                }
            }
            default:
            {
                throw BadResultCode(result_code);
            }
        }
    }

    template<typename T>
    T deserialize_result(const std::string & str, Detail::ResultTypeIsVoid<false>)
    {
        return Deserialize<T>(str);
    }

    template<typename>
    void deserialize_result(const std::string &, Detail::ResultTypeIsVoid<true>)
    {
        // return type is void so there is nothing to return.
    }

    void handle_error(const RPC::Exception& exc);

    std::string sendImpl(std::string inName, const std::string & inArg);

    struct Impl;
    boost::scoped_ptr<Impl> mImpl;
};


} } // namespace Stacked::RPC


#endif // STACKED_RPC_CLIENT_H
