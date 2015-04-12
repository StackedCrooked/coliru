
#include <type_traits>
#include <memory>
#include <tuple>
#include <cstdint>
#include <cstddef>

template <class T> 
struct MemChunk { 
    T *Data = nullptr;
	size_t Size = 0;
	MemChunk() = default;
	MemChunk(T *Mem, size_t Count): Data(Mem), Size(Count) {}
};

inline size_t AlignUp(size_t A, size_t B) {
	return (A + (B - 1)) & ~(B - 1);
}

inline bool IsAligned(char const *Ptr, size_t Alignment) {
	return (reinterpret_cast<size_t>(Ptr) & (Alignment-1)) == 0;
}

// alignof() never returns more than alignas(std::max_align_t),
// but sometimes we have stricter alignment requirements/desires
template <class T> struct RequiredAlignment : std::alignment_of<T> {};

template <typename>
using make_size_t = std::size_t;

template <typename... Ts>
struct result {
    std::unique_ptr<char[]> buffer;
    std::tuple<MemChunk<Ts>...> chunks;
};

template <typename...> struct helper;

template <typename T, typename... Ts>
struct helper<T, Ts...> {
    static result<T, Ts...>
    do_(size_t current, std::size_t size, make_size_t<Ts>... rest) {    
        size_t pos = AlignUp(current, RequiredAlignment<T>::value);
        size_t bytes = pos + size * sizeof(T);
        
        auto memory = helper<Ts...>::do_(bytes, rest...);
            
        T* data = reinterpret_cast<T*>(memory.buffer.get() + pos);
        return {std::move(memory.buffer), std::tuple_cat(std::make_tuple(MemChunk<T>{data, size}), memory.chunks)};
    }
};

template <>
struct helper<> {
    static result<>
    do_(size_t size) {
        return {std::unique_ptr<char[]>{new char[size]}};
    }
};

template <typename... Ts>
std::tuple<std::unique_ptr<char[]>, MemChunk<Ts>...>
AllocateContinuousBuffers(make_size_t<Ts>... sizes) {
    auto r = helper<Ts...>::do_(0, sizes...);
    return std::tuple_cat(std::make_tuple<std::unique_ptr<char[]>>(std::move(r.buffer)), r.chunks);
}

// usage example
struct Vertex {
	// or whatever
	float Pos[3];
	float Norm[3];
	float Tan[3];
	float Bit[3];
	float UV[2];
	uint8_t Color[4];
};

template <> 
struct RequiredAlignment<Vertex> 
	: std::integral_constant<size_t, 16> {};

class Mesh {
public:
	explicit Mesh(size_t NumVertices, size_t NumIndices) {
		std::tie(Memory_, VertChunk_, IndexChunk_) 
			= AllocateContinuousBuffers<Vertex, int>(NumIndices, NumVertices);
	}

private:
	std::unique_ptr<char[]> Memory_;
	MemChunk<Vertex> VertChunk_;
	MemChunk<int> IndexChunk_;
};

int main() {
	Mesh m(3, 9);
}
