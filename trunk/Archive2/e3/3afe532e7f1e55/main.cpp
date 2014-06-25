// test from Adrien Hamelin
// adrien.hamelin@irit.fr

#include <iterator>

namespace Memory {

    template <typename Container>
    class Iterator : public std::iterator<std::forward_iterator_tag, typename Container::value_type> {

    public:
        typedef typename Container::value_type type;
        typedef type &                reference;
        typedef type *                pointer;

    protected:
        pointer m_data;

    public:
        Iterator() = default;
        Iterator(Iterator const &) = default;
        Iterator(Container & pointer, size_t index);
        ~Iterator() = default;

        Iterator & operator=(Iterator const &) = default;
        reference operator*() const;
        pointer operator->() const;

        bool operator==(Iterator const & iter) const;
        bool operator!=(Iterator const & iter) const;

        Iterator & operator++();
        Iterator operator++(int);

        Iterator & operator+=(size_t i);

    };

    /***************************************************************************/
    /*** Functions *************************************************************/
    /***************************************************************************/

    //*
    template <typename Container>
    inline auto operator+(Iterator<Container> iter, size_t i) -> decltype(iter += i) {

        return iter += i;

    }
    /*/
    template <typename Container>
    inline Iterator<Container> operator+(Iterator<Container> const & iter, size_t i) {

        auto result(iter);
        return result += i;

    }
    //*/

    /***************************************************************************/
    /*** Constructor ***********************************************************/
    /***************************************************************************/

    template <typename Container>
    inline Iterator<Container>::Iterator(Container & pointer, size_t index)
    : m_data(pointer.data() + index)
    {}

    /***************************************************************************/
    /*** Public functions ******************************************************/
    /***************************************************************************/

    template <typename Container>
    inline auto Iterator<Container>::operator*() const -> reference {

        return *m_data;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator->() const -> pointer {

        return m_data;

    }

    template <typename Container>
    inline bool Iterator<Container>::operator==(Iterator const & iter) const {

        return m_data == iter.m_data;

    }

    template <typename Container>
    inline bool Iterator<Container>::operator!=(Iterator const & iter) const {

        return m_data != iter.m_data;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator++() -> Iterator & {

        ++m_data;
        return *this;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator++(int) -> Iterator {

        auto value(*this);
        ++m_data;
        return m_data;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator+=(size_t i) -> Iterator & {

        m_data += i;
        return *this;

    }

}

// -------------------------------------------------------------------------

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    auto const size = 100u;
    std::vector<unsigned int> indices(size);
    Memory::Iterator<std::vector<unsigned int> > const begin(indices, 0u);

    std::iota(begin, begin + size, 0u);

    for (auto i = 0u; i < size; ++i) {
        if (indices[i] != i) {
            std::cout << "not working, indices[" << i << "] = " << indices[i] << std::endl;
            return 0;
        }
    }
    std::cout << "working" << std::endl;
    return 0;
}

