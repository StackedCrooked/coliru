#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <iterator>
#include <vector>

#include <openssl/bio.h>
#include <openssl/evp.h>

namespace eyeball
{
  namespace base
  {
    namespace base64
    {
      using bio_ptr = std::unique_ptr<BIO, decltype(&BIO_free_all)>;
      std::size_t constexpr chunk_size{ 512 };

      namespace detail
      {
        template <std::size_t N>
        void assert_size()
        { static_assert(N, "invalid array size"); }

        template <typename It>
        void assert_rai()
        {
          static_assert(std::is_same<typename std::iterator_traits<It>::iterator_category,
                                     std::random_access_iterator_tag>::value,
                        "iterator is not random-access (needs to be contiguous)");
        }
      }

      template <typename In_RAI, typename Out_It>
      void encode(In_RAI const begin, In_RAI const end, Out_It const out)
      {
        detail::assert_rai<In_RAI>();

        BIO * const filter{ BIO_new(BIO_f_base64()) };
        BIO_set_flags(filter, BIO_FLAGS_BASE64_NO_NL);

        BIO * const mem{ BIO_new(BIO_s_mem()) };
        BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL);

        bio_ptr const bio{ BIO_push(filter, mem), &BIO_free_all };
        BIO_write(bio.get(), &*begin, std::distance(begin, end) * sizeof(*begin));
        BIO_flush(bio.get());

        char *data{};
        auto const len(BIO_get_mem_data(bio.get(), &data));
        std::copy(data, data + len, out);
      }

      template <typename T>
      std::string encode(T const &cont)
      {
        std::string ret;
        encode(std::begin(cont), std::end(cont), std::back_inserter(ret));
        return ret;
      }

      template <std::size_t N>
      std::string encode(char const (&cont)[N])
      {
        detail::assert_size<N>();

        std::string ret;
        encode(std::begin(cont), std::end(cont) - 1, std::back_inserter(ret));
        return ret;
      }

      template <typename In_RAI, typename Out_It>
      void decode(In_RAI const begin, In_RAI const end, Out_It const out)
      {
        detail::assert_rai<In_RAI>();

        BIO * const filter{ BIO_new(BIO_f_base64()) };
        BIO_set_flags(filter, BIO_FLAGS_BASE64_NO_NL);

        BIO * const mem{ BIO_new_mem_buf(const_cast<void*>(static_cast<void const*>(&*begin)),
                                         std::distance(begin, end)) };
        bio_ptr const bio{ BIO_push(filter, mem), &BIO_free_all };
        bio_ptr const bio_out{ BIO_new(BIO_s_mem()), &BIO_free_all };

        std::array<char, chunk_size> buf{{}};
        for(int inlen{}; (inlen = BIO_read(bio.get(), buf.data(), buf.size())) > 0; )
        { BIO_write(bio_out.get(), buf.data(), inlen); }
        BIO_flush(bio_out.get());

        char *data{};
        auto const len(BIO_get_mem_data(bio_out.get(), &data));
        std::copy(data, data + len, out);
      }

      template <typename T>
      std::string decode(T const &cont)
      {
        std::string ret;
        decode(std::begin(cont), std::end(cont), std::back_inserter(ret));
        return ret;
      }

      template <std::size_t N>
      std::string decode(char const (&cont)[N])
      {
        static_assert(N, "invalid array size");

        std::string ret;
        decode(std::begin(cont), std::end(cont) - 1, std::back_inserter(ret));
        return ret;
      }
    }
  }
}

int main()
{
  using namespace eyeball::base;

  /* Works on arbitrary containers without explicit iterators. */
  std::string const cat{ "cat" };
  auto const cat_encoded(base64::encode(cat));
  std::cout << "cat_encoded: " << cat_encoded << std::endl;
  std::cout << "cat_decoded: " << base64::decode(cat_encoded) << std::endl;

  /* Ignores the null-terminator for string literals. */
  auto const str(base64::encode("kitty"));
  std::cout << "str_encoded: " << str << std::endl;
  std::cout << "str_decoded: " << base64::decode(str) << std::endl;

  /* Verbose, but flexible. Works with ints, doubles, etc. */
  std::vector<char> const v{ 'm', 'e', 'o', 'w' };
  std::string v_encoded;
  base64::encode(v.begin(), v.end(), std::back_inserter(v_encoded));
  std::cout << "v_encoded: " << v_encoded << std::endl;
  std::cout << "v_decoded: ";
  base64::decode(v_encoded.begin(), v_encoded.end(), std::ostream_iterator<char>(std::cout));
  std::cout << std::endl;
}
