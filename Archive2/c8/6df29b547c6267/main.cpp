#include <iostream>
#include <vector>


template <typename Range, typename Runnable>
struct ConditionalRange;

template <typename Range, typename Runnable>
ConditionalRange<Range, Runnable> makeConditionalRange(Range&, Runnable&&);


template <typename Iterator, typename Runnable>
struct ConditionalIterator
{
   private:
      Iterator iterator;
      Iterator end;
      const Runnable& condition;
   public:
      ConditionalIterator(Iterator b, Iterator e, const Runnable& r)
      :
         iterator(b),
         end(e),
         condition(r)
      {
      }
      auto operator*() -> decltype(*iterator)
      {
         return *iterator;
      }
      ConditionalIterator& operator++()
      {
         do
         {
            ++iterator;
         }
         while ( iterator != end && !condition(*iterator) );
         return *this;
      }
      bool operator==(const ConditionalIterator& second)
      {
         return iterator == second.iterator;
      }
      bool operator!=(const ConditionalIterator& second)
      {
         return !(*this == second);
      }
};

template <typename Range, typename Runnable>
struct ConditionalRange
{
   public:
      friend ConditionalRange makeConditionalRange<>(Range&, Runnable&&);
   
   private:
      Range& range;
      Runnable condition;
   
   public:
   
      using iterator_type = ConditionalIterator<decltype(std::begin(range)), Runnable>;
      
      iterator_type begin() const
      {
         auto b = std::begin(range);
         while ( b != std::end(range) && !condition(*b) )
         {
            ++b;
         }
         return { b, std::end(range), condition };
      }
      iterator_type end() const
      {
         return { std::end(range), std::end(range), condition };
      }
   private:
      ConditionalRange(Range& range_, Runnable&& condition_)
      :
         range(range_),
         condition(std::forward<Runnable>(condition_))
      {
      }
};


template <typename Range, typename Runnable>
ConditionalRange<Range, Runnable> makeConditionalRange(Range& range, Runnable&& condition)
{
   static_assert(std::is_same<decltype(condition(*std::begin(range))), bool>::value,
                 "condition must return a boolean value");
   return { range, std::forward<Runnable>(condition) };
}


int main()
{
    int ns[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for ( const auto& n : makeConditionalRange(ns, [](int a) { return a % 2 == 0; }) )
    {
        std::cout << n << " ";
    }
}
