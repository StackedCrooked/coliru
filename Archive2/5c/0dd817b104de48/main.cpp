#ifndef MQTT_V1_BUFFER_SEQUENCE_HPP_
#define MQTT_V1_BUFFER_SEQUENCE_HPP_
#include <boost/array.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>

namespace mqtt {
inline namespace v1 {
template<typename T>
struct make_buffer_sequence_impl
{
    template<typename... As>
    auto operator()(As&&... as) -> boost::array<T, sizeof...(As)> const
    {
        return boost::array<T, sizeof...(As)>{boost::asio::buffer(as)...};
    }
};

template<typename Sequence>
typename boost::fusion::result_of::invoke<
    make_buffer_sequence_impl<boost::asio::mutable_buffer>
  , Sequence
>::type make_buffer_sequence(Sequence& sequence)
{
    static_assert(boost::fusion::traits::is_sequence<Sequence>::value,
                  "Not a Boost.Fusion sequence");
    return boost::fusion::invoke(
        make_buffer_sequence_impl<boost::asio::mutable_buffer>(), sequence);
}

template<typename Sequence>
typename boost::fusion::result_of::invoke<
    make_buffer_sequence_impl<boost::asio::const_buffer>
  , Sequence
>::type make_buffer_sequence(const Sequence& sequence)
{
    static_assert(boost::fusion::traits::is_sequence<Sequence>::value,
                  "Not a Boost.Fusion sequence");
    return boost::fusion::invoke(
        make_buffer_sequence_impl<boost::asio::const_buffer>(), sequence);
}
} // v1
} // mqtt
#endif
