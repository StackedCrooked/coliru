#include <vector>
#include <algorithm>

template<class T, class Allocator = std::allocator<T>>
class LinkedVector : private std::vector<T, Allocator> {
    using VectorType = std::vector<T, Allocator>;
	using IndexVectorType = std::vector<typename VectorType::size_type>;
public:
	using typename VectorType::value_type;
	using typename VectorType::allocator_type;
	using typename VectorType::size_type;
	using typename VectorType::difference_type;
	using typename VectorType::reference;
	using typename VectorType::const_reference;
	using typename VectorType::pointer;
	using typename VectorType::const_pointer;
	using typename VectorType::iterator;
	using typename VectorType::const_iterator;
	using typename VectorType::reverse_iterator;
	using typename VectorType::const_reverse_iterator;

	using VectorType::at;
	using VectorType::operator[];
	using VectorType::front;
	using VectorType::back;
	using VectorType::begin;
	using VectorType::cbegin;
	using VectorType::end;
	using VectorType::cend;
	using VectorType::rbegin;
	using VectorType::crbegin;
	using VectorType::rend;
	using VectorType::crend;
	using VectorType::empty;
	using VectorType::size;
	using VectorType::max_size;
	using VectorType::capacity;
	
    LinkedVector()
        : LinkedVector(Allocator()) {}
    explicit LinkedVector(const Allocator& alloc)
        : VectorType(alloc) {}
	LinkedVector(size_type count, const T& value, const Allocator& alloc = Allocator())
        : VectorType(count, value, alloc), m_links(count) {}
	explicit LinkedVector(size_type count, const Allocator& alloc = Allocator())
        : VectorType(count, alloc), m_links(count) {}
	template<class InputIt>
	LinkedVector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        : VectorType(first, last, alloc), m_links(last - first) {}
	LinkedVector(const LinkedVector& other)
        : VectorType(other), m_links(other.size()) {}
	LinkedVector(const LinkedVector& other, const Allocator& alloc)
        : VectorType(other, alloc), m_links(other.size()) {}
	LinkedVector(LinkedVector&& other)
        : m_links(other.size()), VectorType(std::move(other)) {}
	LinkedVector(LinkedVector&& other, const Allocator& alloc)
        : m_links(other.size()), VectorType(std::move(other), alloc) {}
	LinkedVector(std::initializer_list<T> list, const Allocator& alloc = Allocator())
        : VectorType(list, alloc), m_links(list.size()) {}
	LinkedVector& operator=(const LinkedVector& other) {
        m_links = other.m_links;
	    return VectorType::operator=(other);
    }
	LinkedVector& operator=(LinkedVector&& other) {
        m_links = other.m_links;
    	return VectorType::operator=(std::move(other));
    }
	LinkedVector& operator=(std::initializer_list<T> list) {
        m_links = std::vector<IndexVectorType>(list.size());
	    return VectorType::operator=(list);
    }

	iterator insert(const_iterator pos, const T& value) {
        m_links.insert(pos, IndexVectorType());
	    return VectorType::insert(pos, value);
    }
	iterator insert(const_iterator pos, T&& value) {
        m_links.insert(pos, IndexVectorType());
	    return VectorType::insert(pos, std::move(value));
    }
	iterator insert(const_iterator pos, size_type count, const T& value) {
        m_links.insert(pos, count, IndexVectorType());
    	return VectorType::insert(pos, count, value);
    }
	template<class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last) {
        m_links.insert(pos, last - first, IndexVectorType());
	    return VectorType::insert(pos, first, last);
    }
	iterator insert(const_iterator pos, std::initializer_list<T> list) {
        m_links.insert(pos, list.size(), IndexVectorType());
	    return VectorType::insert(pos, list);
    }
	template<class... Args>
	iterator emplace(const_iterator pos, Args&&... args) {
        m_links.insert(pos, IndexVectorType());
	    return VectorType::emplace(pos, std::forward<Args>(args)...);
    }
	iterator erase(const_iterator pos) {
        m_links.erase(pos);
    	return VectorType::erase(pos);
    }
	iterator erase(const_iterator first, const_iterator last) {
        m_links.erase(first, last);
	    return VectorType::erase(first, last);
    }
	
	void reserve(size_type newCap) {
        VectorType::reserve(newCap);
	    m_links.reserve(newCap);
    }
	void shrink_to_fit() {
        VectorType::shrink_to_fit();
	    m_links.shrink_to_fit();
    }
	void clear() {
        VectorType::clear();
	    m_links.clear();
    }
	void push_back(const T& value) {
        VectorType::push_back(value);
	    m_links.push_back(IndexVectorType());
    }
	void push_back(T&& value) {
        VectorType::push_back(std::move(value));
	    m_links.push_back(IndexVectorType());
    }
	template<class... Args>
	void emplace_back(Args&&... args) {
        VectorType::emplace_back(std::forward<Args>(args)...);
	    m_links.push_back(IndexVectorType());
    }
	void pop_back() {
        VectorType::pop_back();
	    m_links.pop_back();
    }
	void resize(size_type count) {
        VectorType::resize(count);
	    m_links.resize(count);
    }
	void resize(size_type count, const value_type& value) {
        VectorType::resize(count, value);
	    m_links.resize(count);
    }
	void swap(LinkedVector& other) {
        VectorType::swap(other);
	    m_links.swap(other.m_links);
    }
	
	void addLink(size_type from, size_type to) {
        auto& v = m_links.at(from);
	    if (std::find(v.begin(), v.end(), to) == v.end()) {
		    v.push_back(to);
	    }
    }
	void removeLink(size_type from, size_type to) {
        auto& v = m_links.at(from);
	    auto it = std::find(v.begin(), v.end(), to);
	    if (it != v.end()) {
	    	v.erase(it);
    	}
    }
	void clearLink(size_type from) {
        m_links.at(from).clear();
    }
	void clearAllLinks() {
        m_links.clear();
    }
	
	bool isLinked(size_type from, size_type to) const {
        auto& v = m_links.at(from);
    	return std::find(v.begin(), v.end(), to) != v.end();
    }
	
private:
	std::vector<IndexVectorType> m_links;
};

int main() {
    LinkedVector<int> v;
}
