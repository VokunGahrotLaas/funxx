#pragma once

#include <cstddef>
#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait number_natural

template <typename T>
struct number_natural_traits
{
	static constexpr bool is_number_natural = false;
};

template <typename T>
concept is_number_natural = is_number<T> && number_natural_traits<T>::is_number_natural;

// def n0 && nsucc

struct n0
{};

template <is_number_natural Prev>
struct nsucc
{};

// trait number_natural

template <>
struct number_natural_traits<n0>
{
	static constexpr bool is_number_natural = true;
	using prev = n0;
};

template <is_number_natural Prev>
struct number_natural_traits<nsucc<Prev>>
{
	static constexpr bool is_number_natural = true;
	using prev = Prev;
};

using nsucc_f = unary<nsucc>;

template <is_number N>
struct nth_i
{};

template <is_number N>
using nth = typename nth_i<N>::result;

using nth_f = unary<nth>;

template <is_number_natural N>
struct nth_i<N>
{
	using result = N;
};

// impl number

template <>
struct number_traits<n0>
{
	static constexpr bool is_number = true;
	static constexpr size_t value = 0;
};

template <is_number_natural Prev>
struct number_traits<nsucc<Prev>>
{
	static constexpr bool is_number = true;
	static constexpr size_t value = number_value<Prev> + 1;
};

template <>
struct succ_i<n0>
{
	using result = nsucc<n0>;
};

template <is_number_natural N>
struct succ_i<nsucc<N>>
{
	using result = nsucc<nsucc<N>>;
};

using n1 = succ<n0>;
using n2 = succ<n1>;
using n3 = succ<n2>;
using n4 = succ<n3>;
using n5 = succ<n4>;
using n6 = succ<n5>;
using n7 = succ<n6>;
using n8 = succ<n7>;
using n9 = succ<n8>;
using n10 = succ<n9>;

template <>
struct prev_i<n0>
{
	using result = n0;
};

template <is_number_natural N>
struct prev_i<nsucc<N>>
{
	using result = N;
};

template <is_number_natural N>
struct zero_i<N>
{
	using result = n0;
};

} // namespace functional
