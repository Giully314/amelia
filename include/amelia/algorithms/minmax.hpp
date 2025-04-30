// amelia/algorithms/minmax.hpp
// PURPOSE: implement min and max.
// TODO: concepts on type (comparable).

#pragma once

namespace amelia {

template<typename T>
auto min(const T &a, const T &b) -> const T & {
    return a < b ? a : b;
}

template<typename T>
auto max(const T &a, const T &b) -> const T & {
    return a > b ? a : b;
}

} // namespace amelia
