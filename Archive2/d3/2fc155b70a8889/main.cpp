#include <boost/intrusive/slist.hpp>

typedef boost::intrusive::slist_base_hook<> InputBufferSglHook;

class InputBufferSglNode;

class InputBufferSglNode : public InputBufferSglHook
{
public :

    InputBufferSglNode(const void* buffer, size_t size); 

    ~InputBufferSglNode() {};

    // list
    typedef boost::intrusive::slist<InputBufferSglNode, boost::intrusive::cache_last<true>> SglList;
    typedef SglList::iterator InputBufferSglIterator;

    // copy 'size_t' bytes from list to target, if list doesn't have enough space, method shall return false
    static bool copy_buffer_from_list(SglList &list, InputBufferSglIterator &iter, size_t &offset_in_node, const InputBufferSglIterator& end, uint8_t *target, size_t size);

    void reset();

public:
    const void *m_buffer;
    size_t m_size;
};


// empty list
const InputBufferSglNode::SglList s_EMPTY_INPUT_BUFF_SGL = InputBufferSglNode::SglList();

InputBufferSglNode::InputBufferSglNode(const void* buffer, size_t size) :
    InputBufferSglHook(),
    m_buffer(buffer),
    m_size(size)
{
    // empty
}

void InputBufferSglNode::reset()
{
    m_buffer = nullptr;
    m_size = 0;
}

bool InputBufferSglNode::copy_buffer_from_list(SglList &list, InputBufferSglIterator &iter, size_t &offset_in_node, const InputBufferSglIterator& end, uint8_t *target, size_t size)
{
    // implementation
}

int main() {
}
