#ifndef MY_cartesian_HEADER
#define MY_cartesian_HEADER

#include <vector>
#include <forward_list>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iterator>
#include <type_traits>

template<typename It1, typename It2, typename Prod, typename Pred>
class ordered_cartesian_product {
    static_assert(std::is_convertible<typename std::iterator_traits<It1>::iterator_category, std::input_iterator_tag>::value, "It1 should be input iterator");
	static_assert(std::is_convertible<typename std::iterator_traits<It2>::iterator_category, std::input_iterator_tag>::value, "It2 should be input iterator");
public:
	using value_type1 = typename std::iterator_traits<It1>::value_type;
	static_assert(std::is_copy_constructible<value_type1>::value, "value_type1 should be copy constructible");
	using value_type2 = typename std::iterator_traits<It2>::value_type;
	static_assert(std::is_copy_constructible<value_type2>::value, "value_type2 should be copy constructible");
	using value_type = std::result_of_t<Prod(value_type1, value_type2)>;
	static_assert(std::is_copy_constructible<value_type>::value, "value_type should be copy constructible");

private:
	It1 b1, e1;
	size_t s2{};// 第二个序列的长度
	Prod prod;
	struct backup_element {
		value_type1 value;
		size_t count;// 引用计数
	};
	using backup_t = std::forward_list<backup_element>;
	backup_t backup;// 因为It1是input iterator，所以需要将数据进行备份
	struct heap_element {
		value_type value;// 笛卡尔积
		typename backup_t::iterator it1;
		value_type2 v2;
	};
	struct HeapPred {
		Pred pred;
		HeapPred(Pred pred_) : pred{ std::move(pred_) } {}

		bool operator()(heap_element const &a, heap_element const &b) {
			return pred(a.value, b.value);
		}
	} pred;
	std::vector<heap_element> heap;// 最大堆
public:
	ordered_cartesian_product(It1 b1_, It1 e1_, It2 b2, It2 e2, Prod prod_, Pred pred_) :
		b1{ std::move(b1_) }, e1{ std::move(e1_) },
		prod{ std::move(prod_) }, pred{ std::move(pred_) }
	{
		if (b1 != e1) {
			auto head = *b1++;
			backup.push_front(backup_element{ head, 0 });// 不知道第二个序列的长度，只好先初始化为0
			while (b2 != e2) {
				++s2;
				auto tmp = *b2++;
				heap.push_back(
					heap_element{ prod(head, tmp), backup.begin(), std::move(tmp) }
				);// 插入乘积
				std::push_heap(heap.begin(), heap.end(), pred);
			}
			backup.front().count = s2;// 更新引用计数
		}
	}
	// 可以move，不可复制，因为typename backup_t::iterator复制之后失去意义
	ordered_cartesian_product(ordered_cartesian_product const &) = delete;
	ordered_cartesian_product(ordered_cartesian_product &&) = default;
	ordered_cartesian_product& operator=(ordered_cartesian_product const &) = delete;
	ordered_cartesian_product& operator=(ordered_cartesian_product &&) = default;

	auto&& get() const noexcept {
		return heap.front().value;
	}

	void next() {
		assert(!heap.empty());
		// 去掉堆顶的元素
		std::pop_heap(heap.begin(), heap.end(), pred);
		heap_element tmp = std::move(heap.back()); heap.pop_back();
		auto it = tmp.it1++;
		if (--it->count == 0) {
			assert(it == backup.begin());
			backup.pop_front();
		}
		// 添加新元素
		if (tmp.it1 != backup.end()) {
			heap.push_back(
				heap_element{ prod(tmp.it1->value, tmp.v2), tmp.it1, std::move(tmp.v2) }
			);// 插入乘积
		}
		else if (b1 != e1) {
			auto head = *b1; ++b1;
			assert(std::next(it) == backup.end());
			heap.push_back(
				heap_element{
				prod(head, tmp.v2),
				backup.insert_after(it, backup_element{ head, s2 }),
				std::move(tmp.v2)
			});// 插入乘积
		}
		else {
			return;
		}
		std::push_heap(heap.begin(), heap.end(), pred);
	}

	explicit operator bool() const noexcept {
		return !heap.empty();
	}
};

// 输入迭代器
// 若a = b，*++a不一定等于*++b
template<typename It1, typename It2, typename Prod, typename Pred>
class ordered_cartesian_product_iterator : public
	std::iterator<std::input_iterator_tag, typename ordered_cartesian_product<It1, It2, Prod, Pred>::value_type> {
    using base = std::iterator<std::input_iterator_tag, typename ordered_cartesian_product<It1, It2, Prod, Pred>::value_type>;
	using ordered_cartesian_product_t = ordered_cartesian_product<It1, It2, Prod, Pred>;
	ordered_cartesian_product_t* ptr{};
public:
    using value_type = typename base::value_type;
private:
	std::aligned_storage_t<sizeof(value_type), std::alignment_of<value_type>::value> next;

	auto&& get_next() const noexcept {
		assert(ptr);// ptr不空时才有意义
		return reinterpret_cast<const value_type&>(next);
	}
	auto&& get_next() noexcept {
		assert(ptr);// ptr不空时才有意义
		return reinterpret_cast<value_type&>(next);
	}
public:
	ordered_cartesian_product_iterator() = default;
	ordered_cartesian_product_iterator(ordered_cartesian_product_t &obj) : ptr{ &obj } {
		if (obj) new(&next) value_type(obj.get());
	}
	ordered_cartesian_product_iterator(ordered_cartesian_product_iterator const &other) :
		ptr{ other.ptr } {
		if (other.ptr) new(&next) value_type(other.get_next());// copy construct
	}
	ordered_cartesian_product_iterator(ordered_cartesian_product_iterator &&other):
		ptr{ other.ptr } {
		if (other.ptr) new(&next) value_type(std::move(other.get_next()));// move construct
	}
	ordered_cartesian_product_iterator& operator=(ordered_cartesian_product_iterator const &other) {
		if (other.ptr) {// copy other.get_next()
			if (ptr) {
				get_next() = other.get_next();// copy assign
			}
			else {
				new(&next) value_type(other.get_next());// copy construct
			}
		}
		else {
			if (ptr) get_next().~value_type();// destruct
		}
		ptr = other.ptr;
	}
	ordered_cartesian_product_iterator& operator=(ordered_cartesian_product_iterator &&other) {
		if (other.ptr) {// move other.get_next()
			if (ptr) {
				get_next() = std::move(other.get_next());// move assign
			}
			else {
				new(&next) value_type(std::move(other.get_next()));// move construct
			}
		}
		else {
			if (ptr) get_next().~value_type();// destruct
		}
		ptr = other.ptr;
	}
	~ordered_cartesian_product_iterator() {
		if(ptr) get_next().~value_type();
	}

	auto&& operator*() noexcept {
		return get_next();
	}
	auto&& operator*() const noexcept {
		return get_next();
	}
	auto&& operator->() noexcept {
		return &get_next();
	}
	auto&& operator->() const noexcept {
		return &get_next();
	}

	ordered_cartesian_product_iterator& operator++() {
		assert(ptr && *ptr);
		ptr->next();
		if (*ptr) {
			get_next() = ptr->get();
		}
		else {
			get_next().~value_type();
			ptr = nullptr;// 迭代完毕
		}
		return *this;
	}
	ordered_cartesian_product_iterator operator++(int) {
		auto res = *this;
		operator++();

		return res;
	}

	// 只有两个迭代器都无效时相等
	bool operator==(ordered_cartesian_product_iterator const &other) const noexcept {
		return ptr == other.ptr;
	}
	bool operator!=(ordered_cartesian_product_iterator const &other) const noexcept {
		return !operator==(other);
	}
};

// [b1, e1), [b2, e2)应当是排过序的
// prod用于做笛卡尔积
// pred用于排列笛卡尔积的结果
template<typename It1, typename It2, typename Prod, typename Pred>
auto cartesian_product(It1 b1, It1 e1, It2 b2, It2 e2, Prod prod, Pred pred) {
	return ordered_cartesian_product<It1, It2, Prod, Pred>{
		std::move(b1), std::move(e1), std::move(b2), std::move(e2), std::move(prod), std::move(pred) 
	};
}

template<typename C1, typename It2, typename Prod, typename Pred>
auto cartesian_product(C1 const &c1, It2 b2, It2 e2, Prod prod, Pred pred) {
	using It1 = decltype(std::begin(c1));
	return ordered_cartesian_product<It1, It2, Prod, Pred>{	
		std::begin(c1), std::end(c1), std::move(b2), std::move(e2), std::move(prod), std::move(pred) 
	};
}

template<typename It1, typename It2, typename Prod, typename Pred>
auto cartesian_product(std::pair<It1, It1> r1, It2 b2, It2 e2, Prod prod, Pred pred) {
	return ordered_cartesian_product<It1, It2, Prod, Pred>{
		std::move(r1.first), std::move(r1.second), std::move(b2), std::move(e2), std::move(prod), std::move(pred)
	};
}

template<typename It1, typename C2, typename Prod, typename Pred>
auto cartesian_product(std::pair<It1, It1> r1, C2 const &c2, Prod prod, Pred pred) {
	using It2 = decltype(std::begin(c2));
	return ordered_cartesian_product<It1, It2, Prod, Pred>{	
		std::move(r1.first), std::move(r1.second), std::begin(c2), std::end(c2), std::move(prod), std::move(pred)
	};
}

template<typename C1, typename C2, typename Prod, typename Pred>
auto cartesian_product(C1 const &c1, C2 const &c2, Prod prod, Pred pred) {
	using It1 = decltype(std::begin(c1));
	using It2 = decltype(std::begin(c2));
	return ordered_cartesian_product<It1, It2, Prod, Pred>{
		std::begin(c1), std::end(c1), std::begin(c2), std::end(c2), std::move(prod), std::move(pred)
	};
}

template<typename It1, typename It2, typename Prod, typename Pred>
auto cartesian_product_iterator(ordered_cartesian_product<It1, It2, Prod, Pred> &obj) {
	using iterator = ordered_cartesian_product_iterator<It1, It2, Prod, Pred>;
	return std::make_pair(iterator{ obj }, iterator{});
}

#endif

//#include <cartesian.h>
#include <iostream>
#include <functional>
#include <random>

int main() {
    using type = int;
	std::vector<type> a = { 10, 9, 2, 1, 1 }, b, c;

	{
		for (auto a1 : a) for (auto a2 : a) for (auto a3 : a) for (auto a4 : a) b.push_back(a1*a2*a3*a4);
		std::sort(b.begin(), b.end(), std::greater<type>());
	}

	{
		auto prod = std::multiplies<type>();
		auto pred = std::less<type>();
		auto obj1 = cartesian_product(a, a, prod, pred);
		auto it1 = cartesian_product_iterator(obj1);
		auto obj2 = cartesian_product(it1, a, prod, pred);
		auto it2 = cartesian_product_iterator(obj2);
		auto obj3 = cartesian_product(it2, a, prod, pred);
		auto it = cartesian_product_iterator(obj3);

		std::copy(it.first, it.second, std::back_inserter(c));
	}

	std::cout << "equal? " << (b == c) << "\n";
	for (auto val : c) std::cout << val << " ";
	std::cout << "\n";

	return 0;
}