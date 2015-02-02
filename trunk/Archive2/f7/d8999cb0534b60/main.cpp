#include <memory>
#include <algorithm>
#include <iostream>

template<typename T>
class Array
{
public:
    Array() = default;
	Array(const Array<T>& other) : size_(other.size_), p(alloc.allocate(size_, nullptr))
	{
		std::uninitialized_copy_n(other.p, size_, p);
    }
    ~Array() { clear(); }

	std::size_t size() const { return size_; }

	Array<T>& operator=(Array<T> other)
	{
		std::swap(p, other.p);
		std::swap(size_, other.size_);
		return *this;
	}

	      T& operator[](std::size_t index)       { return p[index]; }
	const T& operator[](std::size_t index) const { return p[index]; }

	void insert(const T& value, std::size_t index)
	{
		std::size_t new_size = size_ + 1;
		T* newp = alloc.allocate(new_size, nullptr);
		std::uninitialized_copy_n(p, index, newp);
		new(newp + index)T(value);
		std::uninitialized_copy_n(p + index, size_ - index, newp + index + 1);
		clear();
		size_ = new_size;
		p     = newp;
	}
private:
	std::allocator<T> alloc {};
    std::size_t       size_ {0};
	     T*           p     {nullptr};

	void clear()
	{
		for(std::size_t i = 0; i < size_; ++i)
		    p[i].~T();
		alloc.deallocate(p, size_);
		p = nullptr;
		size_ = 0;
	}
};

int main()
{
	Array<Array<int>> arr;
	arr.insert(Array<int>(), 0);
	arr.insert(Array<int>(), 1);
	arr[0].insert(42, 0);
	arr[0].insert(24, 1);
	arr[1].insert(69, 0);
	arr[1].insert(96, 1);

	for (std::size_t i = 0; i < arr.size(); i++)
		for (std::size_t j = 0; j < arr[i].size(); j++)
			std::cout << '(' << i << ", " << j << "): " << arr[i][j] << '\n';
}
