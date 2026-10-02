// amelia_types.cppm
// PURPOSE: define base types with fixed size.

module;

#include <stdint.h>

export module amelia.types;


export namespace amelia {

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    
    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using ptr_t = uintptr_t;

    template <typename T>
    using non_owned_ptr = T*;
} // namespace amelia
