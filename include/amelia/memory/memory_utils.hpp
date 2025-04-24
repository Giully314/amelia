// amelia/memory/memory_utils.hpp
// PURPOSE:
//
// DESCRIPTION:
//
//

namespace amelia {

template<typename T>
constexpr auto construct_at(void *address) -> void {
    ::new(address) T{};
}

} // namespace amelia
