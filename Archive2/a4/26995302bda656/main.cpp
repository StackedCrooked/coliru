#include <functional>
#include <unordered_map>
#include <memory>

enum class DeliveryMethodType
{
  POST_MASTER,
  BUBBLE,
};
   
class IDeliveryMethod
{
};

class BubbleDelivery : public IDeliveryMethod
{
};

template<typename Key, typename Interface>
class GenericFactory
{
public:

   using FactoryMethod = std::function<std::unique_ptr<Interface> ()>;

   static Key const& Register(Key const& key, FactoryMethod creator)
   {
      s_factoryMethods.insert({key, creator});
      return key;
   }

   static std::unique_ptr<Interface> Create(Key const& key)
   {
      std::unique_ptr<Interface> obj;

      auto it = s_factoryMethods.find(key);
      if (it != s_factoryMethods.end())
      {
         obj = it->second();
      }

      return obj;
   }

private:
   static std::unordered_map<Key, FactoryMethod> s_factoryMethods;
};

template<typename Key, typename Interface>
std::unordered_map<Key, typename GenericFactory<Key, Interface>::FactoryMethod>
GenericFactory<Key, Interface>::s_factoryMethods;

using DeliveryMethodFactory = GenericFactory<DeliveryMethodType, IDeliveryMethod>;

static auto key = DeliveryMethodFactory::Register(DeliveryMethodType::BUBBLE, []() {
      return std::unique_ptr<IDeliveryMethod>(new BubbleDelivery);
});

int main()
{
}