
#include <cstddef>
#include <iostream>

namespace objstd
{
    template <typename data_type> class advance_iterator
    {
        public:
        advance_iterator(data_type* data_ref)
        {
            this->data_reference = data_ref;
        }
        advance_iterator(const advance_iterator& it) = default;
        advance_iterator(advance_iterator&& it) = default;
        virtual bool operator > (const advance_iterator& it) const
        {
            return this->data_reference > it.data_reference;
        }
        virtual bool operator < (const advance_iterator& it) const
        {
            return this->data_reference < it.data_reference;
        }
        bool operator == (const advance_iterator& it) const
        {
            return this->data_reference == it.data_reference;
        }
        bool operator != (const advance_iterator& it) const
        {
            return this->data_reference != it.data_reference;
        }
        virtual bool operator >= (const advance_iterator& it) const
        {
            return (*this).operator>(it) || (*this).operator==(it);
        }
        virtual bool operator <= (const     advance_iterator& it)const
        {
            return (*this).operator<(it) || (*this).operator==(it);
        }
        virtual advance_iterator& operator+=(const size_t skips)
        {
            this->data_reference += skips;
            return *this;
        }
        virtual advance_iterator& operator++()
        {
            *this += 1;
            return *this;
        }
        virtual advance_iterator& operator++(int)
        {
            advance_iterator& state = *this;
            this->operator++();
            return state;
        }
        virtual advance_iterator operator+ (const size_t skips)
        {
            return this->data_reference + skips;
        }
        //must be declared virtual for non-conservational
        virtual data_type& operator*() const
        {
            return *this->data_reference;
        }
        protected:
        data_type* data_reference;
    };
}

namespace objstd
{
    template <typename data_type> class regress_iterator
    {
        public:
        regress_iterator(data_type* data_ref)
        {
            this->data_reference = data_ref;
        }
        regress_iterator(const regress_iterator& it) = default;
        regress_iterator(regress_iterator&& it) = default;
        virtual bool operator > (const regress_iterator& it) const
        {
            return this->data_reference > it.data_reference;
        }
        virtual bool operator < (regress_iterator& it) const
        {
            return this->data_reference < it.data_reference;
        }
        bool operator == (regress_iterator& it) const
        {
            return this->data_reference == it.data_reference;
        }
        bool operator != (regress_iterator& it) const
        {
            return this->data_reference != it.data_reference;
        }
        virtual bool operator >= (regress_iterator& it) const
        {
            return (*this).operator>(it) || (*this).operator==(it);
        }
        virtual bool operator <= (regress_iterator& it)const
        {
            return (*this).operator<(it) || (*this).operator==(it);
        }
        virtual regress_iterator& operator-=(size_t backwards)
        {
            this->data_reference -= backwards;
            return *this;
        }
        virtual regress_iterator& operator--()
        {
            *this -= 1;
            return *this;
        }
        virtual regress_iterator& operator--(int)
        {
            regress_iterator& state = *this;
            this->operator--();
            return state;
        }
        virtual regress_iterator operator- (size_t backwards)
        {
            return this->data_reference - backwards;
        }
        //must be declared virtual for non-conservational
        virtual data_type& operator*() const
        {
            return *this->data_reference;
        }
        protected:
        data_type* data_reference;
    };
}

namespace objstd
{
    template <typename data_type> class bidirectional_iterator : public advance_iterator <data_type>, public regress_iterator <data_type>
    {
public:

    bidirectional_iterator(data_type* data_ref) :
      advance_iterator<data_type>(data_ref),
      regress_iterator<data_type>(data_ref) {
        // do nothing
    }
    };
}

int main() {
  std::cout << "sim\n";
  int x[3];
  objstd::bidirectional_iterator<int> p(x);
}


