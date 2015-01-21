#include <iostream>
#include <typeinfo>
#include <map>
#include <stdexcept>

struct DynamicItem {
    DynamicItem(const std::type_info *type) : type(type) {
	}

	bool is(const std::type_info &type) {
		return *this->type == type;
	}

	const std::type_info *type;
	DynamicItem *next;
	DynamicItem *prev;
};

typedef void (*ItemFunction)(DynamicItem*);
typedef std::map<const char*, ItemFunction> ItemFunctionMap;
#define DISPATCH(functions, type, function) functions[typeid(type).name()] = function<type>

template <class T> struct Item : DynamicItem {
	Item(T theValue) : DynamicItem(&typeid(T)), value(theValue) {
	}

	T value;
};

class List {
public:
	List() : first(NULL), last(NULL) {
	}

	template <class T> void push(T value) {
		DynamicItem *item = new Item<T>(value);

		item->prev = last;

		if (last) {
			last->next = item;
			last = item;
		} else {
			first = item;
			last = item;
		}
	}

	void foreach(ItemFunction function) {
		for (DynamicItem *item = first; item; item = item->next) {
			function(item);
		}
	}

	void foreach(ItemFunctionMap functions) {
		for (DynamicItem *item = first; item; item = item->next) {
			ItemFunction function = functions[item->type->name()];

			if (function) {
				function(item);
			} else {
				throw std::runtime_error(std::string("Can't print type ") + item->type->name());
			}
		}
	}

protected:
	DynamicItem *first;
	DynamicItem *last;
};

//////////////////////

template <class T> void printItem(DynamicItem *dynamicItem) {
	Item<T> *item = static_cast<Item<T>*>(dynamicItem);

	std::cout << item->type->name() << " " << item->value << std::endl;
}

int main(void) {
	ItemFunctionMap functions;

	// Dynamic dispatch table
	DISPATCH(functions, int,    printItem);
	DISPATCH(functions, double, printItem);
	DISPATCH(functions, char,   printItem);
	DISPATCH(functions, int*,   printItem);
	DISPATCH(functions, char*,  printItem);

	List list = List();

	list.push(123);
	list.push(123.456);
	list.push('a');
	list.push(new int(123));
	list.push(new char('a'));
	// Throws exception, because isn't represented in dynamic dispatch table
	// list.push(static_cast<long>(123));

	list.foreach(functions);

	return 0;
}
