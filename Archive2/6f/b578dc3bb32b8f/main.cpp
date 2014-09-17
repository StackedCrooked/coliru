#include <iostream>
#include <memory>
#include <vector>

class Screen final {
private:
    struct Item
	{
		virtual ~Item() = default;
		virtual void draw() = 0;
	};

	template <typename Drawable>
	struct Proxy : public Item
	{
		Drawable m_drawable;

		template <typename T>
		Proxy(T &&t)
			: m_drawable(std::move(t))
		{
		}

		void draw() override
		{
			m_drawable.draw();
		}
	};

	std::vector<std::unique_ptr<Item>> m_items;

public:
	template <typename Drawable>
	void add(Drawable &&drawable)
	{
		using RealType = typename std::decay<Drawable>::type;

		m_items.push_back(std::make_unique<Proxy<RealType>>(std::forward<Drawable>(drawable)));
	}

	void draw()
	{
		for (auto &d : m_items)
			d->draw();
	}
};





class Triangle {
public:
	void draw()
	{
		std::cout << "I'm a triangle" << std::endl;
	}
};

class Rectangle {
public:
	void draw()
	{
		std::cout << "I'm a rectangle" << std::endl;
	}
};

int main() {
	Screen s;

	s.add(Triangle());
	s.add(Rectangle());

	s.draw();

	return 0;
}