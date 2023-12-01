#pragma once

#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait number_natural

template <typename T>
struct integer_rec_traits
{
	static constexpr bool is_integer_rec = false;
	static constexpr bool is_neg = false;
	static constexpr bool is_pos = false;
};

template <typename T>
concept is_integer_rec = is_integer<T> && integer_rec_traits<T>::is_integer_rec;

template <typename T>
concept is_neg_integer_rec = is_integer_rec<T> && integer_rec_traits<T>::is_neg;

template <typename T>
concept is_pos_integer_rec = is_integer_rec<T> && integer_rec_traits<T>::is_pos;

// def i0 && iprev && isucc

struct i0
{};

template <is_neg_integer_rec Next>
struct iprev
{};

template <is_pos_integer_rec Prev>
struct isucc
{};

// trait number_natural

template <>
struct integer_rec_traits<i0>
{
	static constexpr bool is_integer_rec = true;
	static constexpr bool is_neg = true;
	static constexpr bool is_pos = true;
};

template <is_neg_integer_rec Prev>
struct integer_rec_traits<iprev<Prev>>
{
	static constexpr bool is_integer_rec = true;
	static constexpr bool is_neg = true;
	static constexpr bool is_pos = false;
};

template <is_pos_integer_rec Prev>
struct integer_rec_traits<isucc<Prev>>
{
	static constexpr bool is_integer_rec = true;
	static constexpr bool is_neg = false;
	static constexpr bool is_pos = true;
};

// impl number

template <>
struct integer_traits<i0>
{
	static constexpr bool is_integer = true;
	static constexpr bool is_zero = true;
	static constexpr bool is_strict_negative = false;
	static constexpr bool is_strict_positive = false;
	static constexpr long long value = 0;
};

template <is_neg_integer_rec Next>
struct integer_traits<iprev<Next>>
{
	static constexpr bool is_integer = true;
	static constexpr bool is_zero = false;
	static constexpr bool is_strict_negative = true;
	static constexpr bool is_strict_positive = false;
	static constexpr auto value = number_value<Next> - 1;
};

template <is_pos_integer_rec Prev>
struct integer_traits<isucc<Prev>>
{
	static constexpr bool is_integer = true;
	static constexpr bool is_zero = false;
	static constexpr bool is_strict_negative = false;
	static constexpr bool is_strict_positive = true;
	static constexpr auto value = number_value<Prev> + 1;
};

template <>
struct succ_i<i0>
{
	using result = isucc<i0>;
};

template <is_neg_integer_rec N>
struct succ_i<iprev<N>>
{
	using result = N;
};

template <is_pos_integer_rec N>
struct succ_i<isucc<N>>
{
	using result = isucc<isucc<N>>;
};

using i1 = succ<i0>;
using i2 = succ<i1>;
using i3 = succ<i2>;
using i4 = succ<i3>;
using i5 = succ<i4>;
using i6 = succ<i5>;
using i7 = succ<i6>;
using i8 = succ<i7>;
using i9 = succ<i8>;
using i10 = succ<i9>;

template <>
struct prev_i<i0>
{
	using result = iprev<i0>;
};

template <is_neg_integer_rec N>
struct prev_i<iprev<N>>
{
	using result = iprev<iprev<N>>;
};

template <is_pos_integer_rec N>
struct prev_i<isucc<N>>
{
	using result = N;
};

using im1 = prev<i0>;
using im2 = prev<im1>;
using im3 = prev<im2>;
using im4 = prev<im3>;
using im5 = prev<im4>;
using im6 = prev<im5>;
using im7 = prev<im6>;
using im8 = prev<im7>;
using im9 = prev<im8>;
using im10 = prev<im9>;

template <is_integer_rec N>
struct zero_i<N>
{
	using result = i0;
};

} // namespace functional
