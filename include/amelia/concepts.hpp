// amelia/concepts.hpp
// PURPOSE: Define general concepts.

#pragma once

#include <amelia/type_traits.hpp>
#include <amelia/types.hpp>

namespace amelia {

template<typename T>
concept Destructible = IsNoThrowDestructibleV<T>;

template<typename T, typename U>
concept SameAs = IsSameV<T, U>;

} // namespace amelia
