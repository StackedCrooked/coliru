// test from Adrien Hamelin
// adrien.hamelin@irit.fr

#include <cstddef>

namespace Memory {
    namespace internal {

        enum ClassType {
            ARRAY,
            VECTOR
        };

        template <typename T> class BlockTemplate;
        template <typename T, ClassType classType> class Base;

    }

    class OctreeModel;

    template <typename T> class Iterator;
    template <typename DataContainer, typename IndexContainer> class IndexedVertexIterator;
    template <typename Container> class VertexIterator;

    template <typename T> using Array = internal::Base<T, internal::ARRAY>;
    template <typename T> using Vector = internal::Base<T, internal::VECTOR>;

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
#ifdef __GNUC__
        inline typename std::enable_if<is_empty<Args...>::value && std::is_trivial<T>::value>::type construct_f(
                T *, size_t, Args &&...) {
#else
        inline typename std::enable_if<is_empty<Args...>::value && std::is_trivially_default_constructible<T>::value>::type construct_f(
                T *, size_t, Args &&...) {
#endif
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
#ifdef __GNUC__
        inline typename std::enable_if<!(is_empty<Args...>::value && std::is_trivial<T>::value) &&
                                       !(is_single<Args...>::value && std::is_same<T, first_decay<Args...> >::value)>::type construct_f(
                T * data, size_t size, Args &&... args) {
#else
        inline typename std::enable_if<!(is_empty<Args...>::value && std::is_trivially_default_constructible<T>::value) &&
                                       !(is_single<Args...>::value && std::is_same<T, first_decay<Args...> >::value)>::type construct_f(
                T * data, size_t size, Args &&... args) {
#endif

            // placement new
            for (auto i = 0u; i < size; ++i, ++data)
                ::new((void *)data) T(std::forward<Args>(args)...);

        }

        // i do not think move construct can be optimized away, but if it is not movable you'll want to call copy instead
        template <typename T, typename Iter>
        inline typename std::enable_if<std::is_move_constructible<T>::value, T *>::type moveConstruct_f(T * data, Iter values, size_t size) {

            for (auto i = 0u; i < size; ++i, ++data, ++values)
                ::new((void *)data) T(std::move<T>(*values));

            return data;

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

            template <typename... Args> void construct(size_t i, Args &&... args); // call constructor on the cell given with the given parameters
            template <typename... Args> void construct_n(size_t begin, size_t size, Args &&... args);
            template <typename... Args> void constructAll(Args &&... args);

            // call copy constructor
            void copyConstruct(size_t i, const_type & value);
            template <typename Iter> type * copyConstruct_n(size_t begin, size_t size, Iter values);
            template <typename Iter> type * copyConstructAll(Iter values);

            // call move constructor
            void moveConstruct(size_t i, type && value); // if zero, use the minimum size between the two blocks
            template <typename Iter> type * moveConstruct_n(size_t begin, size_t size, Iter values);
            template <typename Iter> type * moveConstructAll(Iter values);

            // call destructor
            void deconstruct(size_t i) const;
            void deconstruct_n(size_t begin, size_t size) const;
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
        inline void BlockTemplate<T>::construct(size_t i, Args &&... args) {

            assert (i < m_size);

            ::new((void *)(data() + i)) type(std::forward<Args>(args)...);

        }

        template <typename T>
        template <typename... Args>
        inline void BlockTemplate<T>::construct_n(size_t begin, size_t size, Args &&... args) {

            assert(begin + size <= m_size);

            construct_f(data() + begin, size, std::forward<Args>(args)...);

        }

        template <typename T>
        template <typename... Args>
        inline void BlockTemplate<T>::constructAll(Args &&... args) {

            construct_f(data(), m_size, std::forward<Args>(args)...);

        }

        template <typename T>
        inline void BlockTemplate<T>::copyConstruct(size_t i, const_type & value) {

            assert (i < m_size);

            ::new((void *)(data() + i)) type(value);

        }

        template <typename T>
        template <typename Iter>
        inline auto BlockTemplate<T>::copyConstruct_n(size_t begin, size_t size, Iter values) -> type * {

            assert(begin + size <= m_size);
            VERIFY_IS_ITER(Iter)

            return std::uninitialized_copy_n(values, size, data() + begin);

        }

        template <typename T>
        template <typename Iter>
        inline auto BlockTemplate<T>::copyConstructAll(Iter values) -> type * {

            VERIFY_IS_ITER(Iter)

            return std::uninitialized_copy_n(values, m_size, data());

        }

        template <typename T>
        inline void BlockTemplate<T>::moveConstruct(size_t i, type && value) {

            assert (i < m_size);

            ::new((void *)(data() + i)) type(std::move<type>(value));

        }

        template <typename T>
        template <typename Iter>
        inline auto BlockTemplate<T>::moveConstruct_n(size_t begin, size_t size, Iter values) -> type * {

            assert(begin + size <= m_size);
            VERIFY_IS_ITER(Iter)

            return moveConstruct_f(data() + begin, values, size);

        }

        template <typename T>
        template <typename Iter>
        inline auto BlockTemplate<T>::moveConstructAll(Iter values) -> type * {

            VERIFY_IS_ITER(Iter)

            return moveConstruct_f(data(), values, m_size);

        }

        template <typename T>
        inline void BlockTemplate<T>::deconstruct(size_t i) const {

            assert(i < m_size);

            m_saved = false;
            (cData() + i)->~type();

        }

        template <typename T>
        inline void BlockTemplate<T>::deconstruct_n(size_t begin, size_t size) const {

            assert(begin + size <= m_size);

            m_saved = false;
            deconstruct_f(cData() + begin, size);

        }

        template <typename T>
        inline void BlockTemplate<T>::deconstructAll() const {

            m_saved = false;
            deconstruct_f(cData(), m_size);

        }

        /***************************************************************************/
        /*** Protected functions ***************************************************/
        /***************************************************************************/

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

#ifdef _MSC_VER
#   define MEMORY_ITERATOR_INHERIT(name) name(Container * pointer, size_t index, size_t blockSize) : IteratorBase{pointer, index, blockSize} {}
#else
#   define MEMORY_ITERATOR_INHERIT(name) using parent::IteratorBase;
#endif

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
            size_t relativeSize(IteratorBase const & iter) const; // idem than operator- but with no conversion to ptrdiff_t, and safe to use both way ab or ba

            bool operator==(IteratorBase const & iter) const;
            bool operator!=(IteratorBase const & iter) const;
            bool operator<(IteratorBase const & iter) const;
            bool operator<=(IteratorBase const & iter) const;
            bool operator>(IteratorBase const & iter) const;
            bool operator>=(IteratorBase const & iter) const;

            // reserved for internal use
            block_type * block() const;
            size_t blockSize() const;
            size_t index() const;

        protected:
            void addToDataPointer(size_t i);
            void removeFromDataPointer(size_t i);

        };

        /***************************************************************************/
        /*** Functions *************************************************************/
        /***************************************************************************/

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
        size_t IteratorBase<Container>::relativeSize(IteratorBase const & iter) const {

            size_t result = 0u;

            if (m_currentBlock > iter.m_currentBlock)
                result = (m_currentBlock - iter.m_currentBlock) * m_blockSize;
            else
                result = (iter.m_currentBlock - m_currentBlock) * m_blockSize;

            if (m_index > iter.m_index)
                return result + (m_index - iter.m_index);
            else
                return result + (iter.m_index - m_index);

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

        template <typename Container>
        auto IteratorBase<Container>::block() const -> block_type * {

            return m_currentBlock;

        }

        template <typename Container>
        size_t IteratorBase<Container>::blockSize() const {

            return m_blockSize;

        }

        template <typename Container>
        size_t IteratorBase<Container>::index() const {

            return m_index;

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

            m_index -= i;

            // if we want to access the previous block
            if (m_index >= m_blockSize) { // >= because it's unsigned
                m_index %= m_blockSize;
                --m_currentBlock;
            }

        }

        /***************************************************************************/
        /*** Private functions *****************************************************/
        /***************************************************************************/

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
        MEMORY_ITERATOR_INHERIT(Iterator)
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
    /*** Constructor ***********************************************************/
    /***************************************************************************/

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

    /***************************************************************************/
    /*** Protected functions ***************************************************/
    /***************************************************************************/

    /***************************************************************************/
    /*** Private functions *****************************************************/
    /***************************************************************************/

}

// -------------------------------------------------------------------------

#include <algorithm>

#define VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Iter) static_assert(verifyIsNotOurOwnIter<Iter>::value, "Iter problem, should not be false")

namespace Memory {
    namespace internal {

        struct copy_tag {};
        struct copy_construct_tag {};
        struct move_construct_tag {};

        template<class T, class R = void>
        struct enable_if_type {
            typedef R type;
        };

        template<class T, class Enable = void>
        struct verifyIsNotOurOwnIter {
            static bool const value = true;
        };

        template<class T>
        struct verifyIsNotOurOwnIter<T, typename enable_if_type<typename T::block_type>::type> {
            static bool const value = false;
        };

        template <typename Block, typename Iter>
        inline void solo_fromBlockCopy(Block const * block, size_t begin, Iter & values, size_t size) {

            values = std::copy_n(block->cData() + begin, size, values);

        }

        template <typename Block, typename Iter>
        inline void solo_toBlockCopy(Block * block, size_t begin, Iter & values, size_t size) {

            std::copy_n(values, size, block->data() + begin);
            std::advance(values, size);

        }

        template <typename Block, typename Iter>
        inline void solo_copyConstruct(Block * block, size_t begin, Iter & values, size_t size) {

            block->copyConstruct_n(begin, size, values);
            std::advance(values, size);

        }

        template <typename Block, typename Iter>
        inline void solo_moveConstruct(Block * block, size_t begin, Iter & values, size_t size) {

            block->moveConstruct_n(begin, size, values);
            std::advance(values, size);

        }

        template <typename Block, typename Iter, typename Func>
        Iter generic_solo(Block * block, size_t begin, Iter iter, size_t size, size_t blockSize, Func func) {

            // the memory is divided in blocks, so first fill the current block if it is not full,
            // then copy all full blocks, to finally copy the last remaining block if it is not full

            if (size == 0u)
                return iter;

            // if we do not start at the end of a block, we fill it until the end of it or size
            if (begin > 0u) {
                auto const firstBlockSize = std::min(blockSize - begin, size);
                func(block, begin, iter, firstBlockSize);
                size -= firstBlockSize;
                ++block;
            }

            for (; size >= blockSize; ++block, size -= blockSize)
                func(block, 0u, iter, blockSize);

            if (size > 0u)
                func(block, 0u, iter, size);

            return iter;

        }

        template <typename BlockSource, typename BlockDest>
        inline void multi_copy(BlockSource const * source, size_t beginSource, BlockDest * dest, size_t beginDest, size_t size) {

            std::copy_n(source->cData() + beginSource, size, dest->data() + beginDest);

        }

        template <typename BlockSource, typename BlockDest>
        inline void multi_copyConstruct(BlockSource const * source, size_t beginSource, BlockDest * dest, size_t beginDest, size_t size) {

            dest->copyConstruct_n(beginDest, size, source->cData() + beginSource);

        }

        template <typename BlockSource, typename BlockDest>
        inline void multi_moveConstruct(BlockSource const * source, size_t beginSource, BlockDest * dest, size_t beginDest, size_t size) {

            dest->moveConstruct_n(beginDest, size, source->cData() + beginSource);

        }

        template <typename T, typename V, typename Func>
        void generic_multi(Iterator<T> first, size_t size, Iterator<V> result, Func func) {

            // same principles as the one above, except we have blocks as input and output
            // if the blocks are aligned, we are in the same case as above
            // else we want to always start at a beginning of a destination block

            if (size == 0u)
                return;

            auto const blockSize = first.blockSize();
            auto const * source = first.block();
            auto * dest = result.block();

            auto const beginDestIndex = result.index();
            auto beginSrcIndex = first.index();

            // blocks are aligned, simple case, same as above
            if (beginDestIndex == beginSrcIndex) {
                if (beginDestIndex > 0u) {
                    auto const firstBlockSize = std::min(blockSize - beginDestIndex, size);
                    func(source, beginSrcIndex, dest, beginDestIndex, firstBlockSize);
                    size -= firstBlockSize;
                    ++dest; ++source;
                }

                for (; size >= blockSize; ++dest, ++source, size -= blockSize)
                    func(source, 0u, dest, 0u, blockSize);

                if (size > 0u)
                    func(source, 0u, dest, 0u, size);
            }
            else {
                // if we do not start at the beginning of a destination block, we make it so
                if (beginDestIndex > 0u) {
                    auto const destShift = blockSize - beginDestIndex - 1u;

                    if (beginDestIndex < beginSrcIndex) {
                        auto const srcShift = blockSize - beginSrcIndex - 1u;

                        if (size > destShift) {
                            func(source, beginSrcIndex, dest, beginDestIndex, srcShift);
                            func(++source, 0u, dest++, beginDestIndex + srcShift, destShift - srcShift);
                            size -= destShift;
                        }
                        else {
                            if (size > srcShift) {
                                func(source, beginSrcIndex, dest, beginDestIndex, srcShift);
                                func(++source, 0u, dest, beginDestIndex + srcShift, size - srcShift);
                            }
                            else
                                func(source, beginSrcIndex, dest, beginDestIndex, size);
                            return;
                        }
                    }
                    else {
                        if (size > destShift) {
                            func(source, beginSrcIndex, dest++, beginDestIndex, destShift);
                            size -= destShift;
                        }
                        else {
                            func(source, beginSrcIndex, dest, beginDestIndex, size);
                            return;
                       }
                    }

                    beginSrcIndex = (beginSrcIndex + destShift) % blockSize;
                }

                auto const firstHalfSize = blockSize - beginSrcIndex - 1u;
                auto const secondHalfSize = blockSize - firstHalfSize;

                for (; size >= blockSize; size -= blockSize) {
                    func(source, beginSrcIndex, dest, 0u, firstHalfSize);
                    func(++source, 0u, dest++, firstHalfSize, secondHalfSize);
                }

                if (size > firstHalfSize) {
                    func(source, beginSrcIndex, dest, 0u, firstHalfSize);
                    func(++source, 0u, dest, firstHalfSize, size - firstHalfSize);
                }
                else if (size > 0u)
                    func(source, beginSrcIndex, dest, 0u, size);
            }

        }

        template <typename T, typename Size, typename Iter>
        inline Iter generic(Iterator<T> first, Size size, Iter result, copy_tag) {

            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Iter);
            return generic_solo(first.block(), first.index(), result, size, first.blockSize(), solo_fromBlockCopy<typename Iterator<T>::block_type, Iter>);

        }

        template <typename T, typename Size, typename Iter>
        inline Iterator<T> generic(Iter first, Size size, Iterator<T> result, copy_tag) {

            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Iter);
            generic_solo(result.block(), result.index(), first, size, result.blockSize(), solo_toBlockCopy<typename Iterator<T>::block_type, Iter>);
            return std::next(result, size);

        }

        template <typename T, typename Size, typename Iter>
        inline Iterator<T> generic(Iter first, Size size, Iterator<T> result, copy_construct_tag) {

            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Iter);
            generic_solo(result.block(), result.index(), first, size, result.blockSize(), solo_copyConstruct<typename Iterator<T>::block_type, Iter>);
            return std::next(result, size);

        }

        template <typename T, typename Size, typename Iter>
        inline Iterator<T> generic(Iter first, Size size, Iterator<T> result, move_construct_tag) {

            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Iter);
            generic_solo(result.block(), result.index(), first, size, result.blockSize(), solo_moveConstruct<typename Iterator<T>::block_type, Iter>);
            return std::next(result, size);

        }

        template <typename T, typename Size, typename V>
        inline Iterator<V> generic(Iterator<T> first, Size size, Iterator<V> result, copy_tag) {

            generic_multi(first, size, result, multi_copy<typename Iterator<T>::block_type, typename Iterator<V>::block_type>);
            return std::next(result, size);

        }

        template <typename T, typename Size, typename V>
        inline Iterator<V> generic(Iterator<T> first, Size size, Iterator<V> result, copy_construct_tag) {

            generic_multi(first, size, result, multi_copyConstruct<typename Iterator<T>::block_type, typename Iterator<V>::block_type>);
            return std::next(result, size);

        }

        template <typename T, typename Size, typename V>
        inline Iterator<V> generic(Iterator<T> first, Size size, Iterator<V> result, move_construct_tag) {

            generic_multi(first, size, result, multi_moveConstruct<typename Iterator<T>::block_type, typename Iterator<V>::block_type>);
            return std::next(result, size);

        }

        // no construct for if not with our own iterators
        template <typename Inter, typename Size, typename Outer>
        inline Outer generic(Inter first, Size size, Outer result, copy_tag) {

            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Inter);
            VERIFY_ITER_IS_NOT_OUR_OWN_TYPE(Outer);
            return std::copy_n(first, size, result);

        }

    }
}

// -------------------------------------------------------------------------

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

#ifdef _MSC_VER
#   define MEMORY_BASE_INHERIT(name, parent, T) explicit name(size_t size) : parent(size) {} \
                                                name(std::initializer_list<T> list) : parent(list) {} \
                                                name(size_t size, const_type & copy) : parent(size, copy) {} \
                                                template <typename Iter, typename = typename std::iterator_traits<Iter>::iterator_category> \
                                                    name(size_t size, Iter values) : parent(size, values) {}
#else
#   define MEMORY_BASE_INHERIT(name, parent, T) using parent<T, classType>::parent;
#endif

namespace Memory {
    template <typename T> class Iterator;

    namespace internal {

        // specialized in Array.h or Vector.h, gives the data
        template <typename T, ClassType classType> class Base_0;

        // gives the const methods
        template <typename T, ClassType classType>
        class Base_1 : public Base_0<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)

        protected:
            Base_1(container && memory, size_t size);

        public:
            Base_1() = default;
            explicit Base_1(size_t size);
            Base_1(std::initializer_list<T> list);
            Base_1(size_t size, const_type & copy);
            template <typename Iter, typename = typename std::iterator_traits<Iter>::iterator_category> Base_1(size_t size, Iter values);
            Base_1(Base_1 const &) = default;
            Base_1(Base_1 && base) : Base_0<T, classType>::Base_0(std::move(base)) {}
            ~Base_1() = default;

            // element access
            const_type & at(size_t i) const;
            const_type & operator[](size_t i) const;
            const_type & front() const;
            const_type & back() const;

            // iterators
            const_iterator begin() const;
            const_iterator end() const;
            const_iterator cbegin() const;
            const_iterator cend() const;

            // others
            size_t size() const;
            size_t blockSize() const;

        protected:
            block const & blockAtIndex(size_t i) const;

        };

        // specialization for non-const T, we add all the function that allows modifying it
        template <typename T, ClassType classType>
        class Base_2 : public Base_1<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)

        protected:
            Base_2(container && memory, size_t size) : Base_1<T, classType>::Base_1(std::move(memory), size) {}

        public:
            Base_2() = default;
            Base_2(Base_2 const &) = default;
            Base_2(Base_2 && base) : Base_1<T, classType>::Base_1(std::move(base)) {}
            MEMORY_BASE_INHERIT(Base_2, Base_1, T)
            ~Base_2() = default;

            // element access
            type & at(size_t i);
            type & operator[](size_t i);
            type & front();
            type & back();

            using Base_1<T, classType>::at;
            using Base_1<T, classType>::operator[];
            using Base_1<T, classType>::front;
            using Base_1<T, classType>::back;

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

        protected:
            Base_2(container && memory, size_t size) : Base_1<T, classType>::Base_1(std::move(memory), size) {}

        public:
            Base_2() = default;
            Base_2(Base_2 const &) = default;
            Base_2(Base_2 && base) : Base_1<T const, classType>::Base_1(std::move(base)) {}
            MEMORY_BASE_INHERIT(Base_2, Base_1, T const)
            ~Base_2() = default;

        };

        template <typename T, ClassType classType>
        class Base : public Base_2<T, classType> {

            MEMORY_INTERNAL_TYPEDEFS(T)
            template <typename V, ClassType U> friend class Base_0; // to convert Array to Vector and vice-versa

            // for special iterators
            typedef Base<T, classType> This;

        public:
            typedef T value_type;

        protected:
            Base(container && memory, size_t size) : Base_2<T, classType>::Base_2(std::move(memory), size) {}

        public:
            Base() = default;
            Base(Base const &) = default;
            Base(Base && base) : Base_2<T, classType>::Base_2(std::move(base)) {}
            MEMORY_BASE_INHERIT(Base, Base_2, T)
            ~Base();

            Base & operator=(Base base);
            Base & operator=(std::initializer_list<T> array);

        };

        /***************************************************************************/
        /*** Constructor ***********************************************************/
        /***************************************************************************/

        template <typename T, ClassType classType>
        Base_1<T, classType>::Base_1(container && memory, size_t size)
        : Base_0<T, classType>(std::move(memory), size)
        {}

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
        Base_1<T, classType>::Base_1(std::initializer_list<T> list)
        : Base_0<T, classType>::Base_0(list.size())
        {
            // size is at least 1, otherwise the default constructor is called
            auto const remainingSize = list.size() % Base_0<T, classType>::m_blockSize;

            if (remainingSize > 0u)
                Base_0<T, classType>::memory().emplace_back(remainingSize);

            generic(std::begin(list), list.size(), iterator{ &(Base_0<T, classType>::memory()), 0u, Base_0<T, classType>::m_blockSize }, copy_construct_tag());
        }

        template <typename T, ClassType classType>
        Base_1<T, classType>::Base_1(size_t size, const_type & copy)
        : Base_0<T, classType>::Base_0(size)
        {
            if (size > 0u) {
                auto const remainingSize = size % Base_0<T, classType>::m_blockSize;

                if (remainingSize > 0u)
                    Base_0<T, classType>::memory().emplace_back(remainingSize);

                for (auto && block: Base_0<T, classType>::memory())
                    block.constructAll(copy);
            }
        }

        template <typename T, ClassType classType>
        template <typename Iter, typename>
        Base_1<T, classType>::Base_1(size_t size, Iter values)
        : Base_0<T, classType>::Base_0(size)
        {
            if (size > 0u) {
                auto const remainingSize = size % Base_0<T, classType>::m_blockSize;

                if (remainingSize > 0u)
                    Base_0<T, classType>::memory().emplace_back(remainingSize);

                generic(values, size, iterator{ &(Base_0<T, classType>::memory()), 0u, Base_0<T, classType>::m_blockSize }, copy_construct_tag());
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
        inline auto Base<T, classType>::operator=(Base base) -> Base & {

            Base_0<T, classType>::operator=(base);
            return *this;

        }

        template <typename T, ClassType classType>
        inline auto Base<T, classType>::operator=(std::initializer_list<T> array) -> Base & {

            return operator=(Base(array));

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::at(size_t i) const -> const_type & {

            if (i >= size())
                throw std::out_of_range("Memory::Vector range error");

            return blockAtIndex(i).cData()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::at(size_t i) -> type & {

            if (i >= Base_1<T, classType>::size())
                throw std::out_of_range("Memory::Vector range error");

            return blockAtIndex(i).data()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::operator[](size_t i) const -> const_type & {

            return blockAtIndex(i).cData()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::operator[](size_t i) -> type & {

            return blockAtIndex(i).data()[i % Base_0<T, classType>::m_blockSize];

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::front() const -> const_type & {

            return *(Base_0<T, classType>::memory().front().cData());

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::front() -> type & {

            return *(Base_0<T, classType>::memory().front().data());

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::back() const -> const_type & {

            auto && block = Base_0<T, classType>::memory().back();
            return block.cData()[block.size() - 1u];

        }

        template <typename T, ClassType classType>
        inline auto Base_2<T, classType>::back() -> type & {

            auto && block = Base_0<T, classType>::memory().back();
            return block.data()[block.size() - 1u];

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
        inline auto Base_1<T, classType>::cbegin() const -> const_iterator {

            return begin();

        }

        template <typename T, ClassType classType>
        inline auto Base_1<T, classType>::cend() const -> const_iterator {

            return end();

        }

        template <typename T, ClassType classType>
        inline size_t Base_1<T, classType>::size() const {

            return Base_0<T, classType>::m_size;

        }

        template <typename T, ClassType classType>
        inline size_t Base_1<T, classType>::blockSize() const {

            return Base_0<T, classType>::m_blockSize;

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

        /***************************************************************************/
        /*** Private functions *****************************************************/
        /***************************************************************************/

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
            Base_0(container && memory, size_t size);
            Base_0(Base_0 const &) = default;
            Base_0(Base_0 && array);
            ~Base_0() = default;

            Base_0 & operator=(Base_0 array);

            explicit operator bool() const;
//            Vector<T> vector(); // give the internal memory to the vector, making the array empty. All the other Array pointing on this memory are invalidated
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

        template <typename T>
        Base_0<T, ARRAY>::Base_0(container && memory, size_t size)
        : m_memory  (std::make_shared<container>(std::move(memory)))
        , m_size    (size)
        {}

        template <typename T>
        Base_0<T, ARRAY>::Base_0(Base_0 && array)
        : m_memory  (std::move(array.m_memory))
        , m_size    (array.m_size)
        {
            array.m_size = 0u;
        }

        /***************************************************************************/
        /*** Public functions ******************************************************/
        /***************************************************************************/

        template<typename T>
        inline auto Base_0<T, ARRAY>::operator=(Base_0 array) -> Base_0 & {

            std::swap(m_memory, array.m_memory);
            std::swap(m_size, array.m_size);
            return *this;

        }

        template<typename T>
        inline Base_0<T, ARRAY>::operator bool() const {

            return m_memory.operator bool();

        }

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

        /***************************************************************************/
        /*** Private functions *****************************************************/
        /***************************************************************************/

    }
}

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

