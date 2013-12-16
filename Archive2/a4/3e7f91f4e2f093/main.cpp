#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace ij {
    template<typename T>
    class vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using const_reference = T const&;
        using const_pointer = T const*;
        using const_iterator = T const*;

        vector() : vector(0) {

        }

        explicit vector(size_type size_arg)
            : data_(new value_type[size_arg](), std::default_delete<value_type[]>())
            , size_(size_arg) {

        }

        vector(size_type size_arg, value_type const& value)
            : data_(new value_type[size_arg], std::default_delete<value_type[]>())
            , size_(size_arg) {
            std::fill(data_, data_ + size_, value);
        }

        template<typename It>
        vector(It begin, It end)
            : data_(new value_type[std::distance(begin, end)], std::default_delete<value_type[]>())
            , size_(std::distance(begin, end)) {
            std::move(begin, end, data_.get());
        }

        explicit vector(std::initializer_list<T> list)
            : vector(list.begin(), list.end()) {

        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        const_iterator end() const noexcept {
            return cend();
        }

        const_iterator cbegin() const noexcept {
            return data();
        }

        const_iterator cend() const noexcept {
            return data() + size_;
        }

        const_pointer data() const noexcept {
            return data_.get();
        }

        size_type size() const noexcept {
            return size_;
        }

        bool empty() const noexcept {
            return size() == 0;
        }

        const_reference operator[](std::size_t index) const noexcept {
            return data_->operator[](index);
        }

        const_reference at(std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("std::out_of_range");
            }
            return this->operator[](index);
        }

    private:
        std::shared_ptr<value_type> data_;
        size_type size_;
    };
}

#include <cstddef>
#include <iterator>
#include <utility>

namespace ij {
    namespace detail {
        template<typename Skippee>
        class skipping {
        public:
            using value_type = typename Skippee::value_type;
            using size_type = typename Skippee::size_type;
            using difference_type = typename Skippee::difference_type;
            using const_reference = typename Skippee::const_reference;
            using const_pointer = typename Skippee::const_pointer;
            using const_iterator = typename Skippee::const_iterator;

            skipping(Skippee skippee_arg, std::size_t n_arg)
                : skippee(std::move(skippee_arg))
                , n(n_arg) {

            }

            const_iterator begin() const {
                return cbegin();
            }

            const_iterator end() const {
                return cend();
            }

            const_iterator cbegin() const {
                auto it = skippee.cbegin();
                std::advance(it, n);
                return it;
            }

            const_iterator cend() const {
                return skippee.cend();
            }

        private:
            Skippee skippee;
            std::size_t n;
        };
    }

    template<typename Skippee>
    detail::skipping<Skippee> skip(Skippee skippee, std::size_t n) {
        return detail::skipping<Skippee>(std::move(skippee), n);
    }

    namespace detail {
        template<typename Cyclee>
        class cycling {
        public:
            using value_type = typename Cyclee::value_type;
            using size_type = typename Cyclee::size_type;
            using difference_type = typename Cyclee::difference_type;
            using const_reference = typename Cyclee::const_reference;
            using const_pointer = typename Cyclee::const_pointer;

            class const_iterator : public std::iterator<std::forward_iterator_tag,
                                                        value_type,
                                                        difference_type,
                                                        const_pointer,
                                                        const_reference> {
            public:
                const_reference operator*() const {
                    return *it;
                }

                const_pointer operator->() const {
                    return it.operator->();
                }

                const_iterator& operator++() {
                    if (++it == end) {
                        it = begin;
                    }
                    return *this;
                }

                const_iterator operator++(int) {
                    auto copy = *this;
                    ++*this;
                    return copy;
                }

            private:
                const_iterator(typename Cyclee::const_iterator it_arg,
                               typename Cyclee::const_iterator begin_arg,
                               typename Cyclee::const_iterator end_arg)
                    : it(it_arg), begin(begin_arg), end(end_arg) {

                }

                typename Cyclee::const_iterator it;
                typename Cyclee::const_iterator begin;
                typename Cyclee::const_iterator end;

                friend bool operator==(const_iterator const& a, const_iterator const& b) {
                    return a.it == b.it && a.begin == b.begin && a.end == b.end;
                }

                friend bool operator!=(const_iterator const& a, const_iterator const& b) {
                    return !(a == b);
                }

                friend class cycling;
            };

            explicit cycling(Cyclee cyclee_arg)
                : cyclee(std::move(cyclee_arg)) {

            }

            const_iterator begin() const {
                return cbegin();
            }

            const_iterator end() const {
                return cend();
            }

            const_iterator cbegin() const {
                return const_iterator(cyclee.begin(), cyclee.begin(), cyclee.end());
            }

            const_iterator cend() const {
                return const_iterator(cyclee.end(), cyclee.begin(), cyclee.end());
            }

        private:
            Cyclee cyclee;
        };
    }

    template<typename Cyclee>
    detail::cycling<Cyclee> cycle(Cyclee cyclee) {
        return detail::cycling<Cyclee>(std::move(cyclee));
    }
}

#include <algorithm>
#include <iostream>

int main() {
    ij::vector<int> data{1, 2, 3, 4, 5};
    auto it = ij::skip(ij::cycle(ij::skip(data, 2)), 7).begin();
    for (std::size_t i = 0; i < 20; ++i) {
        std::cout << *it++ << '\n';
    }
    return 0;
}
