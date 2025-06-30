#pragma once

#include <functional/function.hpp>

namespace functional
{

template <typename First, typename Second>
struct pair_t
{
	using first = First;
	using second = Second;
};

template <typename T>
struct pair_traits
{
	static constexpr bool is_pair = false;
};

template <typename T>
concept is_pair = pair_traits<T>::is_pair;

template <typename First, typename Second>
struct pair_traits<pair_t<First, Second>>
{
	static constexpr bool is_pair = true;
};

template <is_pair Pair>
struct first_i
{};

template <is_pair Pair>
using first_t = typename first_i<Pair>::result;

using first_f = func<first_t>;

template <typename Pair = noarg>
using first = apply<first_f, Pair>;

template <typename First, typename Second>
struct first_i<pair_t<First, Second>>
{
	using result = First;
};

template <is_pair Pair>
struct second_i
{};

template <is_pair Pair>
using second_t = typename second_i<Pair>::result;

using second_f = func<second_t>;

template <typename Pair = noarg>
using second = apply<second_f, Pair>;

template <typename First, typename Second>
struct second_i<pair_t<First, Second>>
{
	using result = Second;
};

using pair_f = func<pair_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using pair = apply<pair_f, Lhs, Rhs>;

} // namespace functional
