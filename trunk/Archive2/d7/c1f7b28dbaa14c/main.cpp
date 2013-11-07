#include <functional>
#include <type_traits>
#include <memory>

struct ConcreteExpression {};
struct Type {};

struct DeferredExpression {
    std::shared_ptr<std::function<ConcreteExpression(Type*)>> delay;
    template<typename X> DeferredExpression(
        X&& ref, 
        typename std::enable_if<
            std::is_same<
                decltype(ref(std::declval<Type*>())), 
                ConcreteExpression
            >::value &&
            !std::is_same<DeferredExpression, typename std::decay<X>::type>::value
        >::type* = 0
    ) : delay(std::make_shared<std::function<ConcreteExpression(Type*)>>(std::forward<X>(ref))) {}

    DeferredExpression(const DeferredExpression& ref)
        : delay(ref.delay) {}
    DeferredExpression(DeferredExpression&& other)
        : delay(std::move(other.delay)) {}
};
int main() {
    auto process_lambda = [](Type*) -> ConcreteExpression {
        return ConcreteExpression();
    };
    DeferredExpression d(std::move(process_lambda));
}