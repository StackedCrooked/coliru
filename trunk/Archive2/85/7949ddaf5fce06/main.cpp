#include <cstdio>

namespace prism
{
    template <class T>
    class owner_ptr_t
    {
    private:
        T * m_ptr;
    public:
        owner_ptr_t()
        {
            printf("default owner_ptr_t::owner_ptr_t() this = %X ptr = %X m_ptr = %X\n", this, 0, m_ptr);
            m_ptr = 0;
        }
        owner_ptr_t(T * ptr)
        {
            printf("owner_ptr_t::owner_ptr_t(T * ptr) this = %X ptr = %X m_ptr = %X\n", this, ptr, m_ptr);
            assign(ptr);
        }    
        explicit owner_ptr_t(owner_ptr_t<T>& ptr)
        {
            printf("owner_ptr_t::owner_ptr_t(owner_ptr_t<T>& ptr) this = %X ptr = %X m_ptr = %X\n", this, ptr, m_ptr);
            assign(ptr.release());
        }
        ~owner_ptr_t()
        {
            printf("owner_ptr_t::~owner_ptr_t(void) this = %X ptr = %X m_ptr = %X\n", this, 0, m_ptr);
            unassign();
        }
        
        
        void assign(T* ptr)
        {
            printf("owner_ptr_t::assign(T* ptr) this = %X ptr = %X m_ptr = %X\n", this, ptr, m_ptr);
            unassign();

            if (ptr)
            {
                printf("ref_count = %i\n", ptr->ref_count);
                m_ptr = ptr;
                ++m_ptr->ref_count;
                m_ptr->unit_flags |= 0x40;
            }
        }

        void unassign()
        {
            printf("owner_ptr_t::unassign(void) this = %X ptr = %X m_ptr = %X\n", this, 0, m_ptr);
            if (m_ptr)
            {
                printf("ref_count = %i\n", m_ptr->ref_count);
                m_ptr->destroy();
                --m_ptr->ref_count;
                if (m_ptr->ref_count == 0)
                {
                    printf("add_to_garbage; this = %X", this);
                }
                m_ptr = 0;
            }
        }
        /*
        T* release()
        {
            printf("owner_ptr_t::release(void) this = %X ptr = %X m_ptr = %X\n", this, 0, m_ptr);
            T * current_ptr = m_ptr;
            if (m_ptr)
            {
                printf("ref_count = %i\n", m_ptr->ref_count);
                --m_ptr->ref_count;
                m_ptr->unit_flags &= ~0x40;
                m_ptr = 0;
            }
            return current_ptr;
        }
        owner_ptr_t<T>& operator=(T * ptr)
        {
            assign(ptr);
            return (*this);
        }
        owner_ptr_t<T>& operator=(owner_ptr_t<T>& ptr)
        {
            assign(ptr.release());
            return (*this);
        }
        */
        T* get() const
        {
            return m_ptr;
        }
        T* operator->() const
        {
            return get();
        }
        T*& operator*()
        {
            return m_ptr;
        }
        T* operator~() const
        {
            return get();
        }
    };
    
    class unit_base_t // sizeof(12)
    {
    public:
        unsigned m_vtable;              // +0
        int ref_count;             // +4
        unsigned char unit_flags;       // +8
        // +12

    public:
        unit_base_t()
        {
            m_vtable = 0;
            ref_count = 0;
            unit_flags = 0;
        }
        /* virtual */ void destroy()
        {
            printf("unit_base_t::destroy() this = %X\n", this); 
        }
    };
    
    owner_ptr_t<unit_base_t> create_default_unit()
    {
        unit_base_t * ptr = new unit_base_t();
        owner_ptr_t<unit_base_t> a(ptr);
        return a;
    }
}; // namespace prism

int main(int, char**)
{
    prism::owner_ptr_t<prism::unit_base_t> unit = prism::create_default_unit();
    printf("ref = %i\n", unit->ref_count);
    return 0;
}