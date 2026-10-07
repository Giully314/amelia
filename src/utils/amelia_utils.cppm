// src/amelia_utils;'

export module amelia.utils;

import amelia.types;

namespace amelia {
    export extern "C" {
        auto write32(u64 address, u32 value) -> void;
        auto read32(u64 address) -> u32;
    }
} // namespace amelia