

template<typename Signature>
struct Command;

template<typename R, typename ...Args>
struct Command<R(Args...)>
{
    using result_type = R;
    using argument_type = std::tuple<Args...>;
};


using Id = int;
using Duration = int; // seconds


// declare commands
// this code is included in both the server and the client
struct CreateSleeper : Command<Id()> {};
struct StartSleeper : Command<void(Id, Duration)> {};
struct StopSleeper : Command<void(Id)> {};


struct Server
{
    template<typename CommandType>
    void registerCommand(std::function<typename CommandType::result_type(typename CommandType::argument_type)> func)
    {
        functions_.insert(std::make_pair(Demangle<CommandType>(), [=](const std::string& str) {
            return serialize(func(deserialize<typename CommandType::argument_type>(str)));
        }));            
    }
    
    void handleIncomingMessage(socket& sock, const std::string& msg)
    {
        typedef std::pair<std::string, std::string> NameAndArgs;
        auto nameAndArgs = deserialize<NameAndArgs>(msg);
        sock.write(functions_[nameAndArgs.first](nameAndArgs.second));
    }
}



// server side:
void test_server()
{
    Server server;
    
    server.registerCommand<CreateSleeper>([](){
        Sleeper& sleeper = server.addSleeper();
        return sleeper.id();
    });
    
    server.registerCommand<StartSleeper>([](Id id, Duration duration){
        auto& sleeper = Sleeper::GetById(id);
        sleeper.start(duration);
    };
    
    server.registerCommand<StopSleeper>([](Id id){
        auto& sleeper = Sleeper::GetById(id);
        sleeper.stop();
    };
});


// client side
void test_client()
{
    Client client;
    
    Id sleeper1 = client.send<CreateSleeper>();
    Id sleeper2 = client.send<CreateSleeper>();
    Id sleeper3 = client.send<CreateSleeper>();
    
    std::future<void> fut1 = client.async_send<StartSleeper>(sleeper1, 3);
    std::future<void> fut2 = client.async_send<StartSleeper>(sleeper2, 5);
    std::future<void> fut3 = client.async_send<StartSleeper>(sleeper3, 1);
    
    fut1.get();
    fut2.get();
    fut3.get();   
}