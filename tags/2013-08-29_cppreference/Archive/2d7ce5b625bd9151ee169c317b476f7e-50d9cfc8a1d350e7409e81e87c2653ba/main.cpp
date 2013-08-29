        template <typename Sequence, typename Fun>
   1         struct bind_sequence : seq::true_sequence {
   2             using subsequence_type = seq::result_of::as_sequence<wheels::ResultOf<Fun(ValueType<Sequence>)>>;
   3         public:
   4             template <typename SequenceF, typename FunF>
   5             bind_sequence(SequenceF&& source, FunF&& fun)
   6             : source(std::forward<SequenceF>(source)), fun(std::forward<FunF>(fun)) {
   7                 if(!seq::empty(source)) load_next();
   8             }
   9
  10             using value_type = ValueType<subsequence_type>;
  11             using reference = value_type;
  12
  13             bool empty() const { return seq::empty(source) && current && seq::empty(*current); }
  14             value_type front() const { return seq::front(*current); }
  15             void pop_front() { load_next(); }
  16             bind_sequence before(bind_sequence const&) const;
  17
  18         private:
  19             void load_next() {
  20                 current = as_sequence(fun(seq::front(source)));
  21                 seq::pop_front(source);
  22             }
  23
  24             Sequence source;
  25             Fun fun;
  26             detail::optional<subsequence_type> current;
  27         };
