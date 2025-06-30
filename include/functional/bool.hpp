#pragma once

#include <functional/function.hpp>

namespace functional
{

struct True
{};

struct False
{};

template <typename T>
struct bool_traits
{
	static constexpr bool is_bool = false;
};

template <typename T>
concept is_bool = bool_traits<T>::is_bool;

template <typename T>
concept is_true = is_bool<T> && bool_traits<T>::value;

template <typename T>
concept is_false = is_bool<T> && !bool_traits<T>::value;

template <>
struct bool_traits<True>
{
	static constexpr bool is_bool = true;
	static constexpr bool value = true;
};

template <>
struct bool_traits<False>
{
	static constexpr bool is_bool = true;
	static constexpr bool value = false;
};

template <is_bool Bool, typename IfTrue, typename IfFalse>
struct ifthenelse_i
{};

template <is_bool Bool, typename IfTrue, typename IfFalse>
using ifthenelse_t = typename ifthenelse_i<Bool, IfTrue, IfFalse>::result;

using ifthenelse_f = func<ifthenelse_t>;

template <typename Bool = noarg, typename IfTrue = noarg, typename IfFalse = noarg>
using ifthenelse = apply<ifthenelse_f, Bool, IfTrue, IfFalse>;

template <is_true Bool, typename IfTrue, typename IfFalse>
struct ifthenelse_i<Bool, IfTrue, IfFalse>
{
	using result = IfTrue;
};

template <is_false Bool, typename IfTrue, typename IfFalse>
struct ifthenelse_i<Bool, IfTrue, IfFalse>
{
	using result = IfFalse;
};

template <is_bool Bool>
struct Not_i
{
	using result = True;
};

template <is_bool Bool>
using Not_t = typename Not_i<Bool>::result;

using Not_f = func<Not_t>;

template <typename Bool = noarg>
using Not = apply<Not_f, Bool>;

template <is_true True>
struct Not_i<True>
{
	using result = False;
};

template <is_bool Lhs, is_bool Rhs>
struct And_i
{
	using result = False;
};

template <is_bool Lhs, is_bool Rhs>
using And_t = typename And_i<Lhs, Rhs>::result;

using And_f = func<And_t>;

template <typename Lhs = noarg, is_bool Rhs = noarg>
using And = apply<And_f, Lhs, Rhs>;

template <is_true Lhs, is_true Rhs>
struct And_i<Lhs, Rhs>
{
	using result = True;
};

template <is_bool Lhs, is_bool Rhs>
struct Or_i
{
	using result = False;
};

template <is_bool Lhs, is_bool Rhs>
using Or_t = typename Or_i<Lhs, Rhs>::result;

using Or_f = func<Or_t>;

template <typename Lhs = noarg, is_bool Rhs = noarg>
using Or = apply<Or_f, Lhs, Rhs>;

template <is_bool Lhs, is_bool Rhs>
	requires is_true<Lhs> || is_true<Rhs>
struct Or_i<Lhs, Rhs>
{
	using result = True;
};

template <is_bool Lhs, is_bool Rhs>
struct Xor_i
{
	using result = False;
};

template <is_bool Lhs, is_bool Rhs>
using Xor_t = typename Xor_i<Lhs, Rhs>::result;

using Xor_f = func<Xor_t>;

template <typename Lhs = noarg, is_bool Rhs = noarg>
using Xor = apply<Xor_f, Lhs, Rhs>;

template <is_bool Lhs, is_bool Rhs>
	requires(is_true<Lhs> != is_true<Rhs>)
struct Xor_i<Lhs, Rhs>
{
	using result = True;
};

template <bool>
struct Bool_i
{};

template <>
struct Bool_i<true>
{
	using result = True;
};

template <>
struct Bool_i<false>
{
	using result = False;
};

template <bool B>
using Bool = typename Bool_i<B>::result;

} // namespace functional
