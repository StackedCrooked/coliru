#include <memory>

struct Foo : public std::enable_shared_from_this<Foo>
{
};

int main()
{
	auto sharedFoo = std::make_shared<Foo>();
	std::shared_ptr<Foo> nonDeletingSharedFoo(sharedFoo.get(), [](void*){});
	nonDeletingSharedFoo.reset();
	sharedFoo->shared_from_this(); // throws std::bad_weak_ptr
}