#include <future>

struct Message {
    std::string text;
};
enum errType { success, failure };

struct MyClass
{
    std::future<errType> async_sendMessage(Message msg) {
        auto fut = std::async(std::bind(&MyClass::sendMessage, this, msg));
        return fut;
    }
  private:
    errType sendMessage(Message msg) {
        return {};
    }
};

int main()
{
    MyClass object;
    Message msg { "say hi for me" };
    auto fut = object.async_sendMessage(msg);

    errType result = fut.get();

    return result == success;
}
