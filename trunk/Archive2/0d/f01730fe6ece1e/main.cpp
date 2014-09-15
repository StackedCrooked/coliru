#ifndef NERD_UTILS_SMALLVECTOR_H
#define NERD_UTILS_SMALLVECTOR_H

#include <utils/smallallocator.h>
#include <type_traits>
#include <utility>
#include <iterator>

namespace nerd {
namespace utils {

template<typename T>
class alignas(T) SmallVectorBase {
public:
   typedef T value_type;
   typedef T *iterator;
   typedef const T *const_iterator;

public:
   SmallVectorBase(const SmallVectorBase&) = delete;
   SmallVectorBase(SmallVectorBase&&) = delete;

protected:
   SmallVectorBase(T *smallBuffer, T *smallBufferEnd)
      :m_begin(smallBuffer), m_current(smallBuffer), m_end(smallBufferEnd) {

   }

   SmallVectorBase(const SmallVectorBase& other, T *smallBuffer, T *smallBufferEnd)
      :m_begin(smallBuffer), m_current(smallBuffer), m_end(smallBufferEnd)
   {
      assign(other.begin(), other.end());
   }

   SmallVectorBase(SmallVectorBase&& other, T *smallBuffer, T *smallBufferEnd) {
      if(!other.isSmall()) {
         m_begin = other.m_begin;
         m_current = other.m_current;
         m_end = other.m_end;
         
         // set the other one to be an empty small vector, with small-buffer size 1
         other.m_begin = other.m_current = other.getSmallBuffer();
         other.m_end = other.getSmallBuffer() + 1;
         return;
      }
      m_begin = m_current = smallBuffer;
      m_end = smallBufferEnd;
      assign(std::make_move_iterator(other.begin()), std::make_move_iterator(other.end()));
   }

   bool isSmall() const {
      return m_begin == reinterpret_cast<const char*>(this + 1);
   }

public:
   template<typename InputIterator>
   void assign(InputIterator it, InputIterator ite) {
      for(; it != ite; ++it)
         push_back(*it);
   }

   // push_back, emplace_back
   void push_back(const T& t) {
      emplace_back(t);
   }

   void push_back(T&& t) {
      emplace_back(std::move(t));
   }

   template<typename ...T>
   void emplace_back(T &&... t) {
      resizeImpl(size() + 1, std::forward<T>(t)...);
   }

   // pop_back
   void pop_back() {
      resizeImpl(size() - 1);
   }

   iterator insert(const_iterator pos, const T& t) {
      // pos is end?
      if(pos == m_current) {
         push_back(std::move(t));
         return m_current - 1;
      }

      T *posm = shift(const_cast<T*>(pos));
      *posm = t;
      return posm;
   }

   iterator insert(const_iterator pos, T &&t) {
      // pos is end?
      if(pos == m_current) {
         push_back(std::move(t));
         return m_current - 1;
      }

      T *posm = shift(const_cast<T*>(pos));
      *posm = std::move(t);
      return posm;
   }

   // reserve
   void reserve(std::size_t r) {
      reserveImpl(r);
   }

   // resize
   void resize(std::size_t s) {
      resizeImpl(s);
   }

   void resize(std::size_t s, const T& t) {
      resizeImpl(s, t);
   }

   // size, capacity
   std::size_t size() const {
      return m_current - m_begin;
   }

   std::size_t capacity() const {
      return m_end - m_begin;
   }

   iterator begin() { return m_begin; }
   iterator end() { return m_current; }
   const_iterator begin() const { return m_begin; }
   const_iterator end() const { return m_current; }
   const_iterator cbegin() const { return m_begin; }
   const_iterator cend() const { return m_current; }

private:
   T *getSmallBuffer() {
      reinterpret_cast<T*>(this + 1);
   }

   const T *getSmallBuffer() {
      return reinterpret_cast<const T*>(this + 1);
   }

   T *shift(T *shiftStart) {
      // save, because reserve might invalidate it
      std::size_t offset = shiftStart - m_begin;

      // 1. reserve enough space
      reserveImpl(size() + 1);

      shiftStart = m_begin + offset;

      // 2. shift existing elements one to the right.
      try {
         T *dest = m_current;
         T *source = m_current - 1;
         // the first element on the right side is move-constructed
         construct(dest, std::move(*source));
         dest--;
         source--;
         // the remaining ones are move-assigned
         for(; dest != shiftStart; dest--, source--) {
            *dest = std::move(*source);
         }
      } catch(...) {
         // when an exception is thrown, destruct the extra element again
         destruct(m_current);
         throw;
      }
      return shiftStart;
   }

   void reallocate(std::size_t r) {
      struct Deleter { void operator()(T *t) const { ::operator delete(t); } };
      std::unique_ptr<T, decltype(uninitializedDeleter)> newStorage(
               ::operator new(r * sizeof(T)));

      // 1. copy or move elements to new storage
      const std::size_t numberElements = std::min(r, size());
      T *source = m_begin;
      T *sourceEnd = source + numberElements;
      T *dest = newStorage.get();
      try {
         for(; source != sourceEnd; source++, dest++) {
            new (static_cast<void*>(dest)) T(std::move_if_noexcept(*source));
         }
      } catch(...) {
         // exception was thrown during a copy.. destroy already copied elements and rethrow
         destruct(newStorage.begin(), dest);
         throw;
      }

      // 2. clean the old memory
      ::operator delete(m_begin);

      // 3. set the new pointers
      m_begin = newStorage.release();
      m_current = m_begin + newElements;
      m_end = m_begin + r;
   }

   template<typename ...T>
   void construct(T *b, T &&... t) {
      new (static_cast<void*>(b)) T(std::forward<T>(t));
   }

   template<typename ...T>
   void construct(T *b, T *e, T &&... t) {
      T *originalB = b;
      try {
         // 1. construct new elements between b and e
         for(; b != e; b++) {
            new (static_cast<void*>(b)) T(std::forward<T>(t)...);
         }
      } catch(...) {
         // exception was thrown in constructor. destroy new elements and rethrow
         destruct(originalB, b);
         throw;
      }
   }

   void destruct(T *b) {
      b->~T();
   }

   void destruct(T *b, T *e) {
      // destruct elements between b and e, in reverse order
      e--;
      for(T *rewindEnd = b - 1; e != rewindEnd; e--) {
         e->~T();
      }
   }

   void reserveImpl(std::size_t r) {
      if(m_begin + r > m_end) {
         reallocate(r);
      }
   }

   template<typename ...T>
   void resizeImpl(std::size_t s, T &&... t) {
      std::size_t olds = std::size();
      if(olds < s) {
         // new size is greater. ensure enough capacity
         reserveImpl(s + s / 2);

         // construct the new elements
         std::size_t delta = (s - olds);
         construct(m_current, m_current + delta, std::forward<T>(t)...);
         m_current += delta;
      } else if(olds > s) {
         // new size is smaller
         destruct(m_begin + s, m_current);
         m_current = m_begin + s;
      }
   }

private:
   T *m_begin;
   T *m_current;
   T *m_end;
};

/// @class SmallVector
/// A class that uses the stack or heap depending on a threshould size
template<typename T, int N>
class SmallVector : public SmallVectorBase {
   alignas(T) char m_buffer[sizeof(T) * N];

public:
   SmallVector()
      :SmallVectorBase(reinterpret_cast<T*>(m_buffer), reinterpret_cast<T*>(m_buffer) + N)
   { }

   SmallVector(const SmallVector& other)
      :SmallVectorBase(other, reinterpret_cast<T*>(m_buffer), reinterpret_cast<T*>(m_buffer) + N)
   { }

   SmallVector(SmallVector&& other)
      :SmallVectorBase(std::move(other), reinterpret_cast<T*>(m_buffer), reinterpret_cast<T*>(m_buffer) + N)
   { }
};

}
}
#endif // NERD_UTILS_SMALLVECTOR_H
