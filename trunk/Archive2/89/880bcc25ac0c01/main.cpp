/**
 * libRAlloc License
 *
 * Copyright © 2015 Michał "Griwes" Dominiak
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation is required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 **/
 
// debug only
#include <iostream>
// debug only

#include <cstdint>
#include <vector>
#include <memory>
#include <array>
#include <mutex>
#include <cstddef>
#include <cassert>

#include <experimental/optional>

namespace reaver
{
    class unit {};
}

#ifdef __clang__
# define relaxed_constexpr constexpr
#else
# define relaxed_constexpr inline
#endif

#ifdef __unix__
namespace reaver { namespace ralloc { namespace _unix_detail {
# include <sys/mman.h>
}}}
#endif

namespace stdexp = std::experimental;

namespace reaver
{
    namespace ralloc { inline namespace _v1
    {
        namespace platform
        {
            using memory_allocation_handle = void *;
            using lock = std::mutex;

            constexpr std::size_t chunk_size = 4 * 1024 * 1024;
            constexpr std::size_t min_chunk_size = 4096;
            
            inline void terminate()
            {
                std::terminate();
            }
            
            struct allocation_info
            {
                std::uintptr_t address;
                stdexp::optional<memory_allocation_handle> handle;
            };
            
            allocation_info map(std::size_t size)
            {
                auto address = _unix_detail::mmap(0, chunk_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                return { reinterpret_cast<std::uintptr_t>(address), address };
            }
            
            inline void unmap(memory_allocation_handle handle)
            {
                _unix_detail::munmap(handle, platform::chunk_size);
            }
        }

        template<typename T>
        class ralloc_allocator;

        template<typename T>
        using ralloc_vector = std::vector<T, ralloc_allocator<T>>;

        template<typename T>
        using native_vector = std::vector<T>;

        template<template<typename> class T>
        class basic_heap;

        template<typename T>
        class ralloc_allocator : public std::allocator<T>
        {
        public:
            using heap_type = basic_heap<ralloc_vector>;

            ralloc_allocator(heap_type * heap)
            {
            }

        private:
            heap_type * _heap;
        };

        template<template<typename> class Vector>
        class basic_heap
        {
        public:
            basic_heap();

            void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
            {
                if (size < platform::min_chunk_size)
                {
                    assert("TODO");
                }

                else
                {
                    for (auto bin = _get_bin(size); bin != _bins.end(); ++bin)
                    {
                        std::unique_lock<platform::lock> lock{ bin->lock };
                        
                        if (bin == _bins.end() - 1 && !bin->first)
                        {
                            bin->first = _allocate_chunk();
                        }

                        if (bin->first)
                        {
                            auto chunk = bin->first;
                            bin->first = chunk->next;
    
                            while (chunk->chunk_size >= 2 * size && bin != _bins.begin())
                            {
                                chunk = _split(chunk);
                            }
    
                            chunk->next = nullptr;
                            chunk->prev = nullptr;
                            chunk->bin = nullptr;
                            chunk->allocation_size = size;
                            chunk->state = _chunk_state::allocated;
    
                            return reinterpret_cast<void *>(chunk->address);
                        }
                    }
                }
            }

            void * allocate_clean(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
            {
                auto ptr = allocate(size, alignment);
                auto buf = static_cast<unsigned char *>(ptr);
                std::fill(buf, buf + size, 0);
                return ptr;
            }
            
            void * reallocate(void * ptr, std::size_t new_size);

            void free(void * ptr)
            {
            }

            void flush();

            template<typename T>
            struct deleter
            {
                void operator()(T * ptr) const
                {
                    ptr->~T();
                    if (heap)
                    {
                        heap->free(static_cast<void *>(ptr));
                    }
                }

                basic_heap * heap;
            };

            template<typename T>
            using unique_ptr = std::unique_ptr<T, deleter<T>>;

            template<typename T, typename... Args>
            unique_ptr<T> make_unique(Args &&... args)
            {
                auto ptr = allocate(sizeof(T), alignof(T));
                return { new (ptr) T(std::forward<Args>(args)...), deleter<T>{ this } };
            }

        private:
            static constexpr bool _is_freestanding = std::is_same<Vector<int>, ralloc_vector<int>>();
            static constexpr bool _is_native = std::is_same<Vector<int>, native_vector<int>>();

            static_assert(_is_freestanding || _is_native);

            enum class _chunk_state
            {
                free,
                allocated,
                divided,
                micro_managed
            };

            struct _chunk_descriptor;

            struct _bin
            {
                std::size_t size;
                platform::lock lock;
                _chunk_descriptor * first = nullptr;
            };

            struct _chunk_descriptor
            {
                _bin * bin = nullptr;
                _chunk_descriptor * prev = nullptr;
                _chunk_descriptor * next = nullptr;
                _chunk_state state = _chunk_state::free;
                std::uintptr_t address = 0;
                std::size_t allocation_size = 0;
                std::size_t chunk_size = 0;
                _chunk_descriptor * parent = nullptr;
                _chunk_descriptor * left_child = nullptr;
                _chunk_descriptor * right_child = nullptr;
            };

            struct _chunk
            {
                ~_chunk()
                {
                    if (handle)
                    {
                        platform::unmap(*handle);
                    }
                }
                
                std::uintptr_t begin;
                std::uintptr_t end;
                std::size_t size;
                stdexp::optional<platform::memory_allocation_handle> handle;
                unique_ptr<_chunk_descriptor> descriptor;
            };
            
            _chunk_descriptor * _allocate_chunk()
            {
                auto area = platform::map(platform::chunk_size);
                
                _chunk chunk;
                chunk.begin = area.address;
                chunk.end = area.address + platform::chunk_size;
                chunk.size = platform::chunk_size;
                chunk.handle = area.handle;
                
                chunk.descriptor = make_unique<_chunk_descriptor>();
                auto desc = chunk.descriptor.get();
                
                _save(desc);
                return desc;
            }
            
            _chunk_descriptor * _split(_chunk_descriptor * chunk)
            {
                assert(chunk->bin && chunk->state == _chunk_state::free);
                
                chunk->state = _chunk_state::divided;
                chunk->left_child = make_unique<_chunk_descriptor>().release();
                chunk->left_child->parent = chunk;
                chunk->left_child->address = chunk->address;
                chunk->left_child->chunk_size = chunk->chunk_size / 2;

                chunk->right_child = make_unique<_chunk_descriptor>().release();
                chunk->right_child->parent = chunk;
                chunk->right_child->address = chunk->address + chunk->chunk_size / 2;
                chunk->right_child->chunk_size = chunk->chunk_size / 2;

                _save(chunk->right_child);
                return chunk->left_child;
            }
            
            void _save(_chunk_descriptor * chunk)
            {
                auto bin = _get_bin(chunk->chunk_size);
                std::unique_lock<platform::lock> lock{ bin->lock };
                chunk->bin = bin;
                chunk->prev = nullptr;
                chunk->next = bin->first;
                bin->first = chunk;
            }
            
            struct _chunk_microheap
            {
                std::uint64_t magic = 0x12EA7E120017EA12;
                _chunk_descriptor * descriptor;
            };

            using _bootstrap_type = std::conditional_t<
                _is_freestanding,
                std::array<_chunk_descriptor, 256>,
                reaver::unit
            >;

            using _bootstrap_pos_type = std::conditional_t<
                _is_freestanding,
                std::size_t,
                reaver::unit
            >;

            _bootstrap_type _bootstrap;
            _bootstrap_pos_type _bootstrap_pos = {};
            
            Vector<_chunk> _heap_chunks;
            std::size_t _heap_size;

            static relaxed_constexpr std::size_t _size_to_bin_index(std::size_t size)
            {
                if (size < platform::min_chunk_size)
                {
                    size = platform::min_chunk_size;
                }

                std::size_t ret = -1;
                bool is_power = !(size & (size - 1));
                while (size)
                {
                    size >>= 1;
                    ++ret;
                }
                return ret + !is_power;
            }

            _bin * _get_bin(std::size_t size)
            {
                if (size >= platform::chunk_size)
                {
                    return nullptr;
                }

                return &_bins[_size_to_bin_index(size) - _size_to_bin_index(platform::min_chunk_size)];
            }

            std::array<_bin, _size_to_bin_index(platform::chunk_size) - _size_to_bin_index(platform::min_chunk_size)> _bins;
        };

        using heap = basic_heap<ralloc_vector>;
        using native_heap = basic_heap<native_vector>;

        template<>
        heap::basic_heap() : _heap_chunks{ ralloc_allocator<heap::_chunk>{ this } }
        {
        }

        template<>
        native_heap::basic_heap()
        {
        }

        template<>
        template<>
        heap::unique_ptr<heap::_chunk_descriptor> heap::make_unique<heap::_chunk_descriptor>()
        {
            if (_heap_chunks.empty())
            {
                if (_bootstrap_pos == _bootstrap.size())
                {
                    platform::terminate();
                }

                return { &_bootstrap[_bootstrap_pos++], deleter<heap::_chunk_descriptor>{ nullptr } };
            }

            auto ptr = allocate(sizeof(_chunk_descriptor));
            return { new (ptr) _chunk_descriptor, deleter<heap::_chunk_descriptor>{ this } };
        }
    }}
}

int main()
{
    reaver::ralloc::heap h;
    auto p = h.make_unique<int>(1);
}
