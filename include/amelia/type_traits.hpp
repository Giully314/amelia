// amelia/type_traits.hpp
// PURPOSE:
//

#pragma once

namespace amelia {

// ********************** INTEGRAL CONSTANT **********************

template<typename T, T Val>
struct IntegralConstant {
    using value_type = T;
    using type = IntegralConstant<T, Val>;
    static constexpr T value = Val;
};

// ********************** BOOL CONSTANT **********************

template<bool Val>
using BoolConstant = IntegralConstant<bool, Val>;

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

// ********************** IS SAME **********************

template<typename T1, typename T2>
struct IsSame: FalseType {};

template<typename T>
struct IsSame<T, T>: TrueType {};

template<typename T1, typename T2>
inline constexpr bool IsSameV = IsSame<T1, T2>::value;

// ********************** IS NO THROW DESCRUCTIBLE **********************

template<typename T>
    struct IsNoThrowDestructible: BoolConstant < requires(T object) {
    { object.~T() } noexcept;
}>{};

template<typename T>
inline constexpr bool IsNoThrowDestructibleV = IsNoThrowDestructible<T>::value;

// ********************** IS NO THROW DESCRUCTIBLE **********************

} // namespace amelia
