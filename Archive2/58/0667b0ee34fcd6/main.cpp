#include <future>

struct Message {};
struct errType {};

struct MyClass
{
    std::future<errType> async_sendMessage(Message msg,Message* reply){
        auto fut = std::async(std::bind(&MyClass::sendMessage, this));
        return fut;
    }
  private:
    errType sendMessage() {
        return {};
    }
};

int main()
{
    MyClass object;
    Message msg;
    auto fut = object.async_sendMessage(msg, nullptr);

    errType result = fut.get();
}
