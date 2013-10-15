#include <iostream>
#include <cassert>

struct Item
{
    Item* next;
    int value;
    Item(int value, Item* next) : next{next}, value{value} {}
};

void prepend(Item*& head, Item* newItem)
{
    assert(newItem);
    newItem->next = head;
    head = newItem;
}

Item* slice(Item*& head)
{
    if (head == nullptr) return nullptr;

    auto item = head;
    head = item->next;

    item->next = nullptr;
    return item;
}

void print(Item* item)
{
    for (; item; item = item->next)
         std::cout << item->value;
    std::cout << '\n';
}

Item* reverse(Item* list)
{
    Item* reversedList = nullptr;
    while (auto item = slice(list))
        prepend(reversedList, item);
    return reversedList;
}

int main()
{
    auto list = new Item(1, new Item(2, new Item(3, nullptr)));
    print(list);
    list = reverse(list);
    print(list);
}
