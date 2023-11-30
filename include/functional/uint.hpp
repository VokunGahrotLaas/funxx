#pragma once

#include <cstddef>
#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/natural.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait number_uint

template <typename T>
struct number_uint_traits
{
	static constexpr bool is_number_uint = false;
};

template <typename T>
concept is_number_uint = is_number<T> && number_uint_traits<T>::is_number_uint;

// def

template <size_t N>
struct uint
{};

using u0 = uint<0>;

// trait number_uint

template <size_t N>
struct number_uint_traits<uint<N>>
{
	static constexpr bool is_number_uint = true;
};

// impl number

template <size_t N>
struct number_traits<uint<N>>
{
	static constexpr bool is_number = true;
	static constexpr size_t value = N;
};

template <size_t N>
struct succ_i<uint<N>>
{
	using result = uint<N + 1>;
};

using u1 = succ<u0>;
using u2 = succ<u1>;
using u3 = succ<u2>;
using u4 = succ<u3>;
using u5 = succ<u4>;
using u6 = succ<u5>;
using u7 = succ<u6>;
using u8 = succ<u7>;
using u9 = succ<u8>;
using u10 = succ<u9>;

template <size_t N>
struct prev_i<uint<N>>
{
	using result = uint<N == 0 ? 0 : N - 1>;
};

template <is_number_uint N>
struct zero_i<N>
{
	using result = u0;
};

template <size_t Lhs, size_t Rhs>
struct add_i<uint<Lhs>, uint<Rhs>>
{
	using result = uint<Lhs + Rhs>;
};

template <size_t Lhs, size_t Rhs>
struct mul_i<uint<Lhs>, uint<Rhs>>
{
	using result = uint<Lhs * Rhs>;
};

template <size_t N>
struct even_i<uint<N>>
{
	using result = Bool<N % 2 == 0>;
};

template <size_t N>
struct odd_i<uint<N>>
{
	using result = Bool<N % 2 == 1>;
};

// impl number natural

template <size_t N>
using nthu = typename nth_i<uint<N>>::result;

template <>
struct nth_i<u0>
{
	using result = n0;
};

template <size_t N>
struct nth_i<uint<N>>
{
	using result = nsucc<nthu<N - 1>>;
};

} // namespace functional
