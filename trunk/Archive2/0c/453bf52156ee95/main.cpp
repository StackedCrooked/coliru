#include <cstddef>  
#include <vector>
#include <algorithm> 
#include <functional>
#include <string>
#include <iostream>

namespace to_datagram {
  //============================================================================
  using buffer_t = std::pair < const char*, std::size_t >;
  //============================================================================
  struct fbuffer
  {
    std::vector<char> data_;
    std::size_t       max_length_;
    fbuffer(std::size_t max_length = 0){ init(max_length); }

    void init(std::size_t max_length)
    {
      data_.clear();
      data_.reserve(max_length);
      max_length_ = max_length;
    }

    std::size_t remain_capacity() const { return max_length_ - data_.size(); }
    bool        is_complete()     const { return remain_capacity() == 0; }

    void push(buffer_t* stream)
    {
      // aliasing
      const char* data = stream->first;
      std::size_t len = stream->second;

      auto pushed_length = std::min(len, remain_capacity());
      data_.insert(data_.end(), data, data + pushed_length);

      // update stream
      *stream = buffer_t{ data + pushed_length, len - pushed_length };
    }
  };

  //============================================================================

  static bool is_empty(const buffer_t& stream) { return stream.second == 0; }

  /* constexpr */ std::size_t fixed_header_length()    { return 4; }
  /* cosntexpr */ std::size_t max_packet_length()      { return 4096; }

  std::size_t packet_length(const fbuffer& header)
  {
    short packetlen;
    memcpy(&packetlen, &header.data_[0], sizeof(packetlen));

    return  packetlen;
  }

  bool is_valid_packet_length(std::size_t length)
  {
    return fixed_header_length() <= length && length <= max_packet_length();
  }

  static std::size_t body_length(std::size_t packet_length)
  {
    return packet_length - fixed_header_length();
  }

  using handler_t = std::function < bool(const char*, std::size_t) >;
  using logger_t = std::function < void(const std::string&) >;

  //-----------------------------------------------------------------------------

  class Parser
  {
  public:
    bool read_packet(const char *pp, int len, handler_t handler, logger_t logger)
    {
      buffer_t stream{ pp, len };

      while (true)
      {
        switch (state_)
        {
        case estate::kRecvHeader:     recv_header(estate::kCompleteHeader, &stream); break;
        case estate::kCompleteHeader: on_header(estate::kRecvBody);                break;
        case estate::kRecvBody:       recv_body(estate::kCompleteBody, &stream);   break;
        case estate::kCompleteBody:   on_packet(estate::kRecvHeader, handler);     break;

        case estate::kError:          on_error(logger);  return false;
        }

        if (state_ != estate::kError && state_ != estate::kCompleteBody)
          if (is_empty(stream))
            return true;
      }
      return true;
    }

  private:
    enum class estate {
      kRecvHeader,     // 헤더를 받아야 하는 상태  
      kCompleteHeader, // 헤더를 모두 받은 상태   
      kRecvBody,       // 바디를 받아야 하는 상태 
      kCompleteBody,   // 바디를 모두 받은 상태
      kError           // 에러
    };

    void ChangeState(estate next)
    {
      state_ = next;

      if (next == estate::kRecvHeader)
        header_.init(fixed_header_length());
    }

    void ToErrorState(const std::string& msg)
    {
      state_ = estate::kError;
      err_msg_ = msg;
    }

    void recv_header(estate next, buffer_t* stream)
    {
      header_.push(stream);

      if (header_.is_complete())
        ChangeState(next);
    }

    void on_header(estate next)
    {
      auto length = packet_length(header_);
      if (!is_valid_packet_length(length))
        return ToErrorState("invalid packet length : " + std::to_string(length));

      body_.init(body_length(length));
      ChangeState(next);
    }

    void recv_body(estate next, buffer_t* stream)
    {
      body_.push(stream);

      if (body_.is_complete())
        ChangeState(next);
    }

    void on_packet(estate next, handler_t handler)
    {
      auto   msg = header_.data_;
      auto&  body = body_.data_;
      msg.insert(msg.end(), body.begin(), body.end());

      auto is_success = handler(&msg[0], msg.size());

      if (is_success)
        ChangeState(next);
      else
        ToErrorState("packet handler error");
    };

    void on_error(logger_t logger) { logger(err_msg_); }

    fbuffer header_{ fixed_header_length() };
    fbuffer body_;
    estate  state_{ estate::kRecvHeader };
    std::string err_msg_;
  };

}; // end of namesapce to_datagram


//============================================================================
// test

int main()
{
  using namespace to_datagram;

  auto logger = [](const std::string& msg) { std::cout << msg << std::endl; };
  auto fail_handler = [&](const char* pp, std::size_t len)
  {
    logger("called handler. I'll return false for test");
    return false;
  };
  auto success_handler = [&](const char* pp, std::size_t len)
  {
    logger("called handler. I'll return true for test");
    return true;
  };

  {
    Parser parser;
    auto handler = success_handler;
    short len = 2;
    parser.read_packet((const char*)&len, sizeof(len), handler, logger);
    parser.read_packet("bbbb", 4, handler, logger);
  }

  {
    Parser parser;
    auto handler = success_handler;
    short len = 6;
    parser.read_packet((const char*)&len, sizeof(len), handler, logger);
    parser.read_packet("bbbb", 4, handler, logger);
    parser.read_packet((const char*)&len, sizeof(len), handler, logger);
    parser.read_packet("bbbb", 4, handler, logger);
  }

  {
    Parser parser;
    auto handler = fail_handler;
    short len = 7;
    parser.read_packet((const char*)&len, sizeof(len), handler, logger);
    parser.read_packet("bbbb", 4, handler, logger);
    parser.read_packet("bbbb", 4, handler, logger);
  }

  return 0;
}