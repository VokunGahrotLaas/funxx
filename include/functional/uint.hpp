#pragma once

#include <cstddef>
#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait uint

template <typename T>
struct uint_traits
{
	static constexpr bool is_uint = false;
};

template <typename T>
concept is_uint = is_natural<T> && uint_traits<T>::is_uint;

// def

template <size_t N>
struct uint
{};

using u0 = uint<0>;

// trait uint

template <size_t N>
struct uint_traits<uint<N>>
{
	static constexpr bool is_uint = true;
};

// impl natural

template <size_t N>
struct natural_traits<uint<N>>
{
	static constexpr bool is_natural = true;
	static constexpr bool is_zero = N == 0;
	static constexpr unsigned long long value = N;
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

template <is_uint N>
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

} // namespace functional
