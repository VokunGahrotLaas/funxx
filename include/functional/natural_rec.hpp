#pragma once

#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait number_natural

template <typename T>
struct natural_rec_traits
{
	static constexpr bool is_natural_rec = false;
};

template <typename T>
concept is_natural_rec = is_natural<T> && natural_rec_traits<T>::is_natural_rec;

// def n0 && nsucc

struct n0
{};

template <is_natural_rec Prev>
struct nsucc
{};

// trait number_natural

template <>
struct natural_rec_traits<n0>
{
	static constexpr bool is_natural_rec = true;
};

template <is_natural_rec Prev>
struct natural_rec_traits<nsucc<Prev>>
{
	static constexpr bool is_natural_rec = true;
};

// impl number

template <>
struct natural_traits<n0>
{
	static constexpr bool is_natural = true;
	static constexpr bool is_zero = true;
	static constexpr unsigned long long value = 0;
};

template <is_natural_rec Prev>
struct natural_traits<nsucc<Prev>>
{
	static constexpr bool is_natural = true;
	static constexpr bool is_zero = false;
	static constexpr auto value = number_value<Prev> + 1;
};

template <>
struct succ_i<n0>
{
	using result = nsucc<n0>;
};

template <is_natural_rec N>
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

template <is_natural_rec N>
struct prev_i<nsucc<N>>
{
	using result = N;
};

template <is_natural_rec N>
struct zero_i<N>
{
	using result = n0;
};

} // namespace functional
