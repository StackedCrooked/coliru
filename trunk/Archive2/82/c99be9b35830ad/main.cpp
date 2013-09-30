#include <future>

struct Message {
    Message(Message&&) = default;
    std::string text;
};
enum errType { success, failure };

struct MyClass
{
    std::future<errType> async_sendMessage(Message msg) {
        auto fut = std::async(&MyClass::sendMessage, this, std::move(msg));
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
    auto fut = object.async_sendMessage(std::move(msg));

    errType result = fut.get();

    return result == success;
}
