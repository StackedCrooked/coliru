
template<typename Signature>
struct Command;

template<typename R, typename ...Args>
struct Command<R(Args...)>
{
    using result_type = R;
    using argument_type = std::tuple<Args...>;
};


using PlayerId = uint32_t;
using Name = std::string;



// RPC Commands: name + signature
// (struct name is demangled upon registration)
struct CreatePlayer : Command<PlayerId()> {};
struct DestroyPlayer : Command<void(PlayerId)> {};
struct SetName : Command<void(PlayerId, Name)> {};



