#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
class ByteBuffer {
public:
    typedef char value_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef const value_type& const_reference;
    typedef const value_type* const_pointer;
    class const_iterator:
            public std::iterator<std::bidirectional_iterator_tag,value_type>
    {
    public:
        typedef char value_type;
        typedef value_type& reference;
        typedef value_type* pointer;
        typedef const value_type& const_reference;
        typedef const value_type* const_pointer;
        const_iterator(ByteBuffer* buffer)
        {
            std::cout << &((*buffer)[buffer->read_position()]);
        }

        const_iterator(const const_iterator &other):
            current_(other.current_)
        {
        }

        const_iterator& operator=(const const_iterator& other)
        {
            current_ = other.current_;
            return *this;
        }

        bool operator==(const const_iterator& other) const
        {
            return current_ == other.current_;
        }

        bool operator!=(const const_iterator& other) const
        {
            return current_ != other.current_;
        }

        const_iterator& operator++()
        {
            return *this;
        }

        const_iterator operator++(int)
        {
            return *this;
        }

        const_reference operator*() const
        {
            return *current_;
        }

        const_pointer operator->() const
        {
            return current_;
        }
    private:
        const_pointer current_;
        ByteBuffer* buffer_;
    };

    class iterator:
            public std::iterator<std::bidirectional_iterator_tag,value_type>
    {
    public:
        typedef char value_type;
        typedef value_type& reference;
        typedef value_type* pointer;
        typedef const value_type& const_reference;
        typedef const value_type* const_pointer;

        iterator(ByteBuffer* buffer):
            buffer_(buffer)
        {
        }

        iterator(const iterator &other):
            current_(other.current_)
        {
        }

        iterator& operator=(iterator& other)
        {
            current_ = other.current_;
            return *this;
        }

        bool operator==(const iterator &other) const
        {
            return other.current_ == current_;
        }

        bool operator!=(const iterator& other) const
        {
            return other.current_ != current_;
        }

        iterator& operator++()
        {
            return *this;
        }

        reference operator*()
        {
            return *current_;
        }
        pointer operator->()
        {
            return current_;
        }

        operator const_iterator()
        {
            return const_iterator(buffer_);
        }

    private:
        pointer current_;
        ByteBuffer* buffer_;
    };

    ByteBuffer(size_t size):
        buffer_(size,'\0'),read_position_(0),write_position_(0)
    {
    }

    ~ByteBuffer() {}

    //Get current buffer reading position
    size_t read_position()
    {
        return read_position_;
    }

    //Get current writing position
    size_t write_position()
    {
        return write_position_;
    }

    //Remove all contents of ByteBuffer and reset position to 0
    void clear()
    {
        buffer_.clear();
        read_position_ = 0;
        write_position_ = 0;
    }

    //Resize buffer to buffer_size.
    void resize(size_t buffer_size)
    {
        buffer_.resize(buffer_size);
    }

    std::string& buffer()
    {
        return buffer_;
    }

    //Get buffer full size
    size_t size()
    {
        return buffer_.size();
    }

    /*
     * Read varint(https://developers.google.com/protocol-buffers/docs/encoding#varints)
     * and put into uint32_t
     */
    uint32_t read_varint()
    {
        uint32_t value = 0;
        uint8_t byte;
        uint8_t shift = 0;
        int8_t length = 0;
        const uint8_t* data = reinterpret_cast<const uint8_t*>(buffer_.c_str());
        //Read data until byte & 128 will give 0 or until readed 5 bytes(max value)
        do {
            //Unsigned VarInt can't have length over 5 bytes
            if (length > 5) {
                throw std::runtime_error("VarInt is too long: >5 bytes");
            }
            byte = data[read_position_ + length];
            value |= static_cast<uint8_t>((byte & 0x7f)) << shift;
            shift += 7;
            ++read_position_;
            ++length;
        }
        while ((byte & 0x80) != 0);
        return value;
    }

    std::string read_string()
    {
        uint32_t string_length = read_varint();
        size_t bytes_readed = 0;
        std::string result;
        while(bytes_readed < string_length) {
            result += buffer_[read_position_];
            ++read_position_;
            ++bytes_readed;
        }
        return result;
    }

    int16_t read_short()
    {
        int16_t value = 0;
        buffer_.copy((char*)&value,2,read_position_);
        read_position_ += 2;
        return ntohs(value);
    }

    int32_t read_long()
    {
        int32_t value = 0;
        buffer_.copy((char*)&value,4,read_position_);
        read_position_ += 4;
        return ntohl(value);
    }

    //Put uint32_t as varint into buffer
    void write_varint(uint32_t value)
    {
        while (value > 0x7F) {
          buffer_[write_position_] = (static_cast<uint8_t>(value) & 0x7F) | 0x80;
          value >>= 7;
          ++write_position_;
          ++actual_size_;
        }
        buffer_[write_position_] = static_cast<uint8_t>(value) & 0x7F;
        ++write_position_;
        ++actual_size_;
    }

    void write_string(std::string data)
    {
        size_t length = data.size();
        write_varint(length);
        buffer_ += data;
        actual_size_ += length;
        write_position_ += length;
    }


    char& operator[](size_t position) {
        return buffer_[position];
    }

    ByteBuffer& operator=(value_type value)
    {
        buffer_ = value;
        return *this;
    }

    iterator end() {
        return iterator(this);
    }

    iterator begin() {
        return iterator(this);
    }

    const_iterator cend() {
        const_iterator tmp(this);
        return tmp;
    }

    const_iterator cbegin() {
        const_iterator tmp(this);
        return tmp;
    }
private:
    std::string buffer_;
    size_t read_position_;
    size_t write_position_;
    size_t actual_size_;
};

using boost::asio::ip::tcp;

int main(int argc,char** argv)
{
    std::string hostname = "74.114.88.128";
    boost::asio::io_service io_service;
   // Get a list of endpoints corresponding to the server name.
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(hostname, "80");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);
    
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET /w/ HTTP/1.0\r\n";
    request_stream << "Host: " << hostname << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    // Send the request.
    boost::asio::write(socket, request);
    
    
    ByteBuffer response(1024);
    boost::system::error_code ec;
    boost::asio::read(socket, response,ec);
    return 0;
}
