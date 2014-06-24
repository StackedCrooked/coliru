// test from Adrien Hamelin
// adrien.hamelin@irit.fr

#include <cstddef>

namespace Memory {
    namespace internal {

        enum ClassType {
            ARRAY
        };

        template <typename T> class BlockTemplate;
        template <typename T, ClassType classType> class Base;

    }

    class OctreeModel;

    template <typename T> class Iterator;
    template <typename T> using Array = internal::Base<T, internal::ARRAY>;

}

// -------------------------------------------------------------------------

#include <vector>

namespace Memory {
    namespace internal {

        // gives the basic types
        template <typename T>
        struct typedefs {

            typedef typename std::remove_cv<T>::type type;
            typedef type const                       const_type;

            typedef BlockTemplate<type>              block;
            typedef std::vector<block>               container;

            typedef Iterator<container>              iterator;
            typedef Iterator<container const>        const_iterator;

        };

    }
}

// -------------------------------------------------------------------------

#include <assert.h>
#include <list>
#include <string>

namespace Memory {
    namespace internal {

        class Block {

        protected:
            typedef std::list<Block const *>::const_iterator const_iterator;

            class Manager {
            public:
                std::list<Block const *>loadedBlocks;
                size_t                  byteNumberUsed       = 0;
                size_t                  maxBytePerBlock      = 20000000;   // huge block of allocation are divided into block of that size, TODO (around 20mo)
                size_t                  byteNumberAuthorized = 4000000000; // objectif of maximum memory taken, TODO (around 4go of ram);
                size_t                  blockNumber          = 0;          // used to give a name to the file

                template <typename T>
                size_t maxSizeForBlock() const;
            };

        public:
            static Manager          s_manager;

        private:
            size_t                  m_name;
            size_t                  m_byteSize;
            mutable const_iterator  m_loadedPosition;

        protected:
            Block(size_t byteSize);
            Block(Block const &) = delete;
            Block(Block && block);
            virtual ~Block();

            Block & operator=(Block const &) = delete;
            Block & operator=(Block && block);

        public:
            std::string name() const;
            void clear();

            size_t byteSize() const;

        protected:
            void byteTaken() const;
            void byteFreed() const;

            void used() const;

        private:
            virtual void unload() const = 0;

        };

        /***************************************************************************/
        /*** Inline functions ******************************************************/
        /***************************************************************************/

        //// Public /////////////////////////////////////////////////////////////////

        inline std::string Block::name() const {

            return /*MEMORY_MANAGER_FOLDER + */std::to_string(m_name);

        }

        inline size_t Block::byteSize() const {

            return m_byteSize;

        }

        template <typename T>
        size_t Block::Manager::maxSizeForBlock() const {

            assert(maxBytePerBlock / sizeof(T) > 1); // we need at least to be able to have 2 blocks in memory (for copy purposes)
            return maxBytePerBlock / sizeof(T);

        }

        //// Protected //////////////////////////////////////////////////////////////
        //// Private ////////////////////////////////////////////////////////////////

    }
}

// -------------------------------------------------------------------------

Memory::internal::Block::Manager Memory::internal::Block::s_manager;

/***************************************************************************/
/*** Constructor ***********************************************************/
/***************************************************************************/

Memory::internal::Block::Block(size_t byteSize)
: m_name        (Memory::internal::Block::s_manager.blockNumber++)
, m_byteSize    (byteSize)
{
}

Memory::internal::Block::Block(Block && block)
: m_name            (std::move(block.m_name))
, m_byteSize        (block.m_byteSize)
, m_loadedPosition  (std::move(block.m_loadedPosition))
{
}

Memory::internal::Block::~Block() {

    clear();

}

/***************************************************************************/
/*** Public functions ******************************************************/
/***************************************************************************/

Memory::internal::Block & Memory::internal::Block::operator=(Block && block) {

    clear();
    m_name = std::move(block.m_name);
    m_byteSize = block.m_byteSize;
    m_loadedPosition = std::move(block.m_loadedPosition);
    return *this;

}

void Memory::internal::Block::clear() {

    remove(name().c_str()); // remove the file if present

}

/***************************************************************************/
/*** Protected functions ***************************************************/
/***************************************************************************/

void Memory::internal::Block::byteTaken() const {

    s_manager.byteNumberUsed += byteSize();
    m_loadedPosition = s_manager.loadedBlocks.insert(s_manager.loadedBlocks.cbegin(), this);

    while (s_manager.byteNumberUsed > s_manager.byteNumberAuthorized) {
        s_manager.loadedBlocks.back()->unload();
        s_manager.loadedBlocks.pop_back();
    }

}

void Memory::internal::Block::byteFreed() const {

    assert(s_manager.byteNumberUsed >= byteSize());

    s_manager.byteNumberUsed -= byteSize();
    s_manager.loadedBlocks.erase(m_loadedPosition);
    m_loadedPosition = s_manager.loadedBlocks.cend();

}

void Memory::internal::Block::used() const {

    // does not matter if iter == loadedBlocks.cbegin()
    s_manager.loadedBlocks.splice(s_manager.loadedBlocks.cbegin(), s_manager.loadedBlocks, m_loadedPosition);

}

// -------------------------------------------------------------------------

#include <memory>

namespace Memory {
    namespace internal {

        /* defined function ***********************************************************************************************
         *
         * template <typename T, typename... Args>  void construct_f(T * data, size_t size, Args &&... args)
         * template <typename T, typename Iter>     T * moveConstruct_f(T * data, Iter values, size_t size)
         * template <typename T>                    void deconstruct_f(T const * data, size_t size)
         *
         ******************************************************************************************************************/

        template <typename... Args> struct is_empty : std::integral_constant<bool, sizeof...(Args) == 0> {};
        template <typename... Args> struct is_single : std::integral_constant<bool, sizeof...(Args) == 1> {};

        template <typename... Args> struct first {};
        template <typename T, typename... Args> struct first<T, Args...> { typedef T type; };
        template <> struct first<> { typedef void type; };

        template <typename... Args> using first_decay = typename std::decay<typename first<Args...>::type>::type;

        // if our type is trivially constructible and we have no arguments, we have nothing to do
        template <typename T, typename... Args>
        inline typename std::enable_if<is_empty<Args...>::value && std::is_trivial<T>::value>::type construct_f(
                T *, size_t, Args &&...) {
            // empty

        }

        // if we want to do a copy, we let the std do it
        template <typename T, typename... Args>
        inline typename std::enable_if<is_single<Args...>::value && std::is_same<T, first_decay<Args...> >::value>::type construct_f(
                T * data, size_t size, Args &&... args) {

            std::uninitialized_fill_n(data, size, std::forward<Args>(args)...);

        }

        // else we must call the constructor for every object
        template <typename T, typename... Args>
        inline typename std::enable_if<!(is_empty<Args...>::value && std::is_trivial<T>::value) &&
                                       !(is_single<Args...>::value && std::is_same<T, first_decay<Args...> >::value)>::type construct_f(
                T * data, size_t size, Args &&... args) {

            // placement new
            for (auto i = 0u; i < size; ++i, ++data)
                ::new((void *)data) T(std::forward<Args>(args)...);

        }

        // if type is trivially destructible, we have nothing to do
        template <typename T>
        inline typename std::enable_if<std::is_trivially_destructible<T>::value>::type deconstruct_f(T const *, size_t) {

            // empty

        }

        // else we call the destructor on each value
        template <typename T>
        inline typename std::enable_if<!std::is_trivially_destructible<T>::value>::type deconstruct_f(T const * data, size_t size) {

            for (auto i = 0u; i < size; ++i, ++data)
                data->~T();

        }

    }
}

// -------------------------------------------------------------------------

#define VERIFY_IS_ITER(type) static_assert(std::is_copy_assignable<typename std::iterator_traits<type>::iterator_category>::value, "");

namespace Memory {
    namespace internal {

        template <typename T>
        class BlockTemplate : public Block {

        public:
            typedef typename typedefs<T>::type          type;
            typedef typename typedefs<T>::const_type    const_type;

        private:
            mutable type *          m_memory    = nullptr;
            size_t                  m_size      = s_manager.maxSizeForBlock<type>();
            mutable bool            m_saved     = false;

        public:
            BlockTemplate(); // size is the maximum possible for a block, no constructor called
            explicit BlockTemplate(size_t size); // no constructor called
            BlockTemplate(BlockTemplate const & block) = delete; // copy is your problem, as we do not know the initialized cell
            BlockTemplate(BlockTemplate && block); // a block moved can never be used afterwards
            ~BlockTemplate();

            BlockTemplate & operator=(BlockTemplate const &) = delete;
            BlockTemplate & operator=(BlockTemplate && block);

            type * data();
            const_type * data() const;
            const_type * cData() const;

            size_t size() const;

            template <typename... Args> void constructAll(Args &&... args);

            // call destructor
            void deconstructAll() const;

        private:
            void load() const;
            void unload() const override;
            bool isLoaded() const;

        };

        /***************************************************************************/
        /*** Constructor ***********************************************************/
        /***************************************************************************/

        template <typename T>
        BlockTemplate<T>::BlockTemplate()
        : Block (s_manager.maxSizeForBlock<T>() * sizeof(T))
        {}

        template <typename T>
        BlockTemplate<T>::BlockTemplate(size_t size)
        : Block (std::min(size, s_manager.maxSizeForBlock<T>()) * sizeof(T))
        , m_size(std::min(size, s_manager.maxSizeForBlock<T>()))
        {}

        template <typename T>
        BlockTemplate<T>::BlockTemplate(BlockTemplate && block)
        : Block         (std::move(block))
        , m_memory      (block.m_memory)
        , m_size        (block.m_size)
        , m_saved       (block.m_saved)
        {
            block.m_memory = nullptr;
            block.m_saved = false;
        }

        template <typename T>
        BlockTemplate<T>::~BlockTemplate() {

            if (isLoaded()) {
                m_saved = true; // avoid to write to file
                unload();
            }

        }

        /***************************************************************************/
        /*** Public functions ******************************************************/
        /***************************************************************************/

        template <typename T>
        auto BlockTemplate<T>::operator=(BlockTemplate && block) -> BlockTemplate & {

            // delete if needed
            if (isLoaded()) {
                m_saved = true;
                unload();
            }

            // copy it
            Block::operator=(std::move(block));
            m_memory = block.m_memory;
            m_size = block.m_size;
            m_saved = block.m_saved;

            // remove from source
            block.m_memory = nullptr;
            block.m_saved = false;

            return *this;

        }

        template <typename T>
        inline auto BlockTemplate<T>::data() -> type * {

            m_saved = false;
            return isLoaded() ? (used(), m_memory) : (load(), m_memory);

        }

        template <typename T>
        inline auto BlockTemplate<T>::data() const -> const_type * {

            return cData();

        }

        template <typename T>
        inline auto BlockTemplate<T>::cData() const -> const_type * {

            return isLoaded() ? (used(), m_memory) : (load(), m_memory);

        }

        template <typename T>
        inline size_t BlockTemplate<T>::size() const {

            return m_size;

        }

        template <typename T>
        template <typename... Args>
        inline void BlockTemplate<T>::constructAll(Args &&... args) {

            construct_f(data(), m_size, std::forward<Args>(args)...);

        }

        template <typename T>
        inline void BlockTemplate<T>::deconstructAll() const {

            m_saved = false;
            deconstruct_f(cData(), m_size);

        }

        /***************************************************************************/
        /*** Private functions *****************************************************/
        /***************************************************************************/

        template <typename T>
        void BlockTemplate<T>::load() const {

            assert(!isLoaded());

            // make sure not to take too much memory
            byteTaken();

            // allocate memory but do not call constructor
            m_memory = static_cast<type *>(::operator new(byteSize()));

        }

        template <typename T>
        void BlockTemplate<T>::unload() const {

            assert(isLoaded());

            // deallocate memory but do not call destructors
            ::operator delete(m_memory);
            m_memory = nullptr;

            // bytes no longer taken
            byteFreed();

        }

        template <typename T>
        inline bool BlockTemplate<T>::isLoaded() const {

            return m_memory != nullptr;

        }

    }
}

// -------------------------------------------------------------------------

#include <iterator>

namespace Memory {
    namespace internal {

        template <typename Container>
        class IteratorBase : public std::iterator<std::random_access_iterator_tag, typename Container::value_type::type> {

            // trivial class, the default initialization gives an invalid pointer anyway

        public:
            typedef typename std::conditional<std::is_const<Container>::value,
                typename Container::value_type const, typename Container::value_type>::type             block_type;
            typedef typename std::conditional<std::is_const<Container>::value,
                typename Container::value_type::const_type, typename Container::value_type::type>::type type;
            typedef type &                                                                              reference;
            typedef type *                                                                              pointer;

        protected:
            size_t       m_index;       // index in the current block
            size_t       m_blockSize;
            block_type * m_currentBlock;

        public:
            IteratorBase() = default;
            IteratorBase(Container * pointer, size_t index, size_t blockSize);
            IteratorBase(IteratorBase const &) = default;
            ~IteratorBase() = default;

            IteratorBase & operator=(IteratorBase const &) = default;
            reference operator*() const;
            pointer operator->() const;
            reference operator[](size_t i) const;

            ptrdiff_t operator-(IteratorBase const & iter) const;

            bool operator==(IteratorBase const & iter) const;
            bool operator!=(IteratorBase const & iter) const;
            bool operator<(IteratorBase const & iter) const;
            bool operator<=(IteratorBase const & iter) const;
            bool operator>(IteratorBase const & iter) const;
            bool operator>=(IteratorBase const & iter) const;

        protected:
            void addToDataPointer(size_t i);
            void removeFromDataPointer(size_t i);

        };

        /***************************************************************************/
        /*** Constructor ***********************************************************/
        /***************************************************************************/

        template <typename Container>
        inline IteratorBase<Container>::IteratorBase(Container * pointer, size_t index, size_t blockSize)
        : m_index       (index % blockSize)
        , m_blockSize   (blockSize)
        , m_currentBlock(pointer->data() + (index / m_blockSize))
        {}

        /***************************************************************************/
        /*** Public functions ******************************************************/
        /***************************************************************************/

        template <typename Container>
        inline auto IteratorBase<Container>::operator*() const -> reference {

            return m_currentBlock->data()[m_index];

        }

        template <typename Container>
        inline auto IteratorBase<Container>::operator->() const -> pointer {

            return m_currentBlock->data() + m_index;

        }

        template <typename Container>
        auto IteratorBase<Container>::operator[](size_t i) const -> reference {

            IteratorBase copy(*this);
            copy.addToDataPointer(i);
            return *copy;

        }

        template <typename Container>
        inline ptrdiff_t IteratorBase<Container>::operator-(IteratorBase const & iter) const {

            return static_cast<ptrdiff_t>(m_currentBlock - iter.m_currentBlock) * static_cast<ptrdiff_t>(m_blockSize) +
                    (static_cast<ptrdiff_t>(m_index) - static_cast<ptrdiff_t>(iter.m_index));

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator==(IteratorBase const & iter) const {

            return m_currentBlock == iter.m_currentBlock && m_index == iter.m_index;

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator!=(IteratorBase const & iter) const {

            return m_currentBlock != iter.m_currentBlock || m_index != iter.m_index;

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator<(IteratorBase const & iter) const {

            return (m_currentBlock == iter.m_currentBlock) ? (m_index < iter.m_index) : (m_currentBlock < iter.m_currentBlock);

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator<=(IteratorBase const & iter) const {

            return (m_currentBlock == iter.m_currentBlock) ? (m_index <= iter.m_index) : (m_currentBlock <= iter.m_currentBlock);

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator>(IteratorBase const & iter) const {

            return (m_currentBlock == iter.m_currentBlock) ? (m_index > iter.m_index) : (m_currentBlock > iter.m_currentBlock);

        }

        template <typename Container>
        inline bool IteratorBase<Container>::operator>=(IteratorBase const & iter) const {

            return (m_currentBlock == iter.m_currentBlock) ? (m_index >= iter.m_index) : (m_currentBlock >= iter.m_currentBlock);

        }

        /***************************************************************************/
        /*** Protected functions ***************************************************/
        /***************************************************************************/

        template <typename Container>
        void IteratorBase<Container>::addToDataPointer(size_t i) {

            m_index += i;

            // if we want to access the next block
            if (m_index >= m_blockSize) {
                m_index %= m_blockSize;
                ++m_currentBlock;
            }

        }

        template <typename Container>
        void IteratorBase<Container>::removeFromDataPointer(size_t i) {

            // if we want to access the previous block
            if (m_index < i) {
                m_index += m_blockSize;
                --m_currentBlock;
            }

            m_index -= i;

        }

    }
}

// -------------------------------------------------------------------------

namespace Memory {

    template <typename Container>
    class Iterator : public internal::IteratorBase<Container> {

        // trivial class, the default initialization gives an invalid pointer anyway

        typedef internal::IteratorBase<Container> parent;

    public:
        typedef typename parent::reference  reference;
        typedef typename parent::pointer    pointer;
        typedef typename parent::block_type block_type;

    public:
        Iterator() = default;
        Iterator(Iterator const &) = default;
        using parent::IteratorBase;
        ~Iterator() = default;

        Iterator & operator=(Iterator const &) = default;

        Iterator & operator++();
        Iterator operator++(int);
        Iterator & operator--();
        Iterator operator--(int);

        Iterator & operator+=(size_t i);
        Iterator & operator-=(size_t i);

    };

    /***************************************************************************/
    /*** Functions *************************************************************/
    /***************************************************************************/

    template <typename Container>
    inline auto operator+(Iterator<Container> iter, size_t i) -> decltype(iter += i) {

        return iter += i;

    }

    template <typename Container>
    inline auto operator+(size_t i, Iterator<Container> iter) -> decltype(iter += i) {

        return iter += i;

    }

    template <typename Container>
    inline auto operator-(Iterator<Container> iter, size_t i) -> decltype(iter -= i) {

        return iter -= i;

    }

    template <typename Container>
    inline auto operator-(size_t i, Iterator<Container> iter) -> decltype(iter -= i) {

        return iter -= i;

    }

    /***************************************************************************/
    /*** Public functions ******************************************************/
    /***************************************************************************/

    template <typename Container>
    inline auto Iterator<Container>::operator++() -> Iterator & {

        parent::addToDataPointer(1u);
        return *this;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator++(int) -> Iterator {

        auto value(*this);
        parent::addToDataPointer(1u);
        return value;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator--() -> Iterator & {

        parent::removeFromDataPointer(1u);
        return *this;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator--(int) -> Iterator {

        auto value(*this);
        parent::removeFromDataPointer(1u);
        return value;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator+=(size_t i) -> Iterator & {

        parent::addToDataPointer(i);
        return *this;

    }

    template <typename Container>
    inline auto Iterator<Container>::operator-=(size_t i) -> Iterator & {

        parent::removeFromDataPointer(i);
        return *this;

    }

}

// -------------------------------------------------------------------------

#include <algorithm>
#include <initializer_list>

#define MEMORY_INTERNAL_TYPEDEFS(T) \
    public: \
        typedef typename typedefs<T>::type            type; \
        typedef typename typedefs<T>::const_type      const_type; \
        typedef typename typedefs<T>::iterator        iterator; \
        typedef typename typedefs<T>::const_iterator  const_iterator; \
    \
    /*protected:*/ \
        typedef typename typedefs<T>::block           block; \
        typedef typename typedefs<T>::container       container;

namespace Memory {
    template <typename T> class Iterator;

    namespace internal {

        // specialized in Array.h or Vector.h, gives the data
        template <typename T, ClassType classType> class Base_0;

        // gives the const methods
        template <typename T, ClassType classType>
        class Base_1 : public Base_0<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)

        public:
            explicit Base_1(size_t size);
            ~Base_1() = default;

            // element access
            const_type & operator[](size_t i) const;

            // iterators
            const_iterator begin() const;
            const_iterator end() const;
            
            size_t size() const;

        protected:
            block const & blockAtIndex(size_t i) const;

        };

        // specialization for non-const T, we add all the function that allows modifying it
        template <typename T, ClassType classType>
        class Base_2 : public Base_1<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)

        public:
            using Base_1<T, classType>::Base_1;
            ~Base_2() = default;

            // element access
            type & operator[](size_t i);

            using Base_1<T, classType>::operator[];

            // iterators
            iterator begin();
            iterator end();

            using Base_1<T, classType>::begin;
            using Base_1<T, classType>::end;

        protected:
            block & blockAtIndex(size_t i);

        };

        // specialization for const T, we only need to be able to be constructed from a non-const type
        template <typename T, ClassType classType>
        class Base_2<T const, classType> : public Base_1<T const, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T const)
            
        public:
            using Base_1<T, classType>::Base_1;
            ~Base_2() = default;

        };

        template <typename T, ClassType classType>
        class Base : public Base_2<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)

            // for special iterators
            typedef Base<T, classType> This;

        public:
            typedef T value_type;

        public:
            using Base_2<T, classType>::Base_2;
            ~Base();

        };

        /***************************************************************************/
        /*** Constructor ***********************************************************/
        /***************************************************************************/

        template <typename T, ClassType classType>
        Base_1<T, classType>::Base_1(size_t size)
        : Base_0<T, classType>::Base_0(size)
        {
            if (size > 0u) {
                auto const remainingSize = size % Base_1<T, classType>::m_blockSize;

                if (remainingSize > 0u)
                    Base_0<T, classType>::memory().emplace_back(remainingSize);

                for (auto && block: Base_0<T, classType>::memory())
                    block.constructAll();
            }
        }

        template <typename T, ClassType classType>
        inline Base<T, classType>::~Base() {

            Base_0<T, classType>::clear();

        }

        /***************************************************************************/
        /*** Public functions ******************************************************/
        /***************************************************************************/

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::operator[](size_t i) const -> const_type & {

            return blockAtIndex(i).cData()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::operator[](size_t i) -> type & {

            return blockAtIndex(i).data()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::begin() const -> const_iterator {

            return { &(Base_0<T, classType>::memory()), 0u, Base_0<T, classType>::m_blockSize };

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::begin() -> iterator {

            return { &(Base_0<T, classType>::memory()), 0u, Base_0<T, classType>::m_blockSize };

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::end() const -> const_iterator {

            return { &(Base_0<T, classType>::memory()), size(), Base_0<T, classType>::m_blockSize };

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::end() -> iterator {

            return { &(Base_0<T, classType>::memory()), Base_1<T, classType>::size(), Base_0<T, classType>::m_blockSize };

        }
        
        template <typename T, ClassType classType>
        inline size_t Base_1<T, classType>::size() const {

            return Base_0<T, classType>::m_size;

        }

        /***************************************************************************/
        /*** Protected functions ***************************************************/
        /***************************************************************************/

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::blockAtIndex(size_t i) const -> block const & {

            return Base_0<T, classType>::memory()[i / Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::blockAtIndex(size_t i) -> block & {

            return Base_0<T, classType>::memory()[i / Base_0<T, classType>::m_blockSize];

        }

    }
}

// -------------------------------------------------------------------------

#include <memory>

namespace Memory {

    // Array is declared in memory/declaration.h

    namespace internal {

        template <typename T>
        class Base_0<T, ARRAY> {

            MEMORY_INTERNAL_TYPEDEFS(T)

        protected:
            size_t const                m_blockSize = Block::s_manager.maxSizeForBlock<T>();
            std::shared_ptr<container>  m_memory;// = nullptr
            size_t                      m_size      = 0u;

        public:
            Base_0() = default;
            explicit Base_0(size_t size);
            ~Base_0() = default;

            void clear();

//        protected:
            container & memory();
            container const & memory() const;

        };


        /***************************************************************************/
        /*** Constructor ***********************************************************/
        /***************************************************************************/

        template <typename T>
        Base_0<T, ARRAY>::Base_0(size_t size)
        : m_memory  (std::make_shared<container>(size / m_blockSize))
        , m_size    (size)
        {}

        /***************************************************************************/
        /*** Public functions ******************************************************/
        /***************************************************************************/

        template<typename T>
        void Base_0<T, ARRAY>::clear() {

            if (m_memory.unique()) {
                for (auto && block: memory())
                    block.deconstructAll();
            }

            m_memory = nullptr;
            m_size = 0u;

        }

        /***************************************************************************/
        /*** Protected functions ***************************************************/
        /***************************************************************************/

        template <typename T>
        inline auto Base_0<T, ARRAY>::memory() -> container & {

            return *m_memory;

        }

        template <typename T>
        inline auto Base_0<T, ARRAY>::memory() const -> container const & {

            return *m_memory;

        }

    }
}

// -------------------------------------------------------------------------

#include <iostream>
#include <numeric>

int main()
{
    auto const size = 100u;
    Memory::Array<unsigned int> indices(size);
    auto const begin = std::begin(indices);

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

