// amelia/type_traits.hpp
// PURPOSE:
//

#pragma once

namespace amelia {

template<typename T, T Val>
struct IntegralConstant {
    using value_type = T;
    using type = IntegralConstant<T, Val>;
    static constexpr T value = Val;
};

template<bool Val>
using BoolConstant = IntegralConstant<bool, Val>;

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

template<typename T1, typename T2>
struct IsSame: FalseType {};

template<typename T>
struct IsSame<T, T>: TrueType {};

template<typename T1, typename T2>
inline constexpr bool IsSameV = IsSame<T1, T2>::value;

} // namespace amelia
