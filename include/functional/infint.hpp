#pragma once

#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/list.hpp>
#include <functional/number.hpp>

namespace functional
{

// trait number_infint

template <typename T>
struct infint_traits
{
	static constexpr bool is_infint = false;
	static constexpr bool is_unclean = false;
};

template <typename T>
concept is_infint = is_natural<T> && is_list<T> && infint_traits<T>::is_infint;

template <typename T>
concept is_infint_unclean = is_infint<T> && infint_traits<T>::is_unclean;

// def

struct inf0
{};

using inf0 = inf0;
using inf1 = pair<True, inf0>;

// trait number_infint

template <>
struct infint_traits<inf0>
{
	static constexpr bool is_infint = true;
	static constexpr bool is_unclean = true;
};

template <is_list_pair N>
	requires is_bool<first<N>> && is_infint<second<N>>
struct infint_traits<N>
{
	static constexpr bool is_infint = true;
	static constexpr bool is_unclean = is_false<first<N>> && infint_traits<second<N>>::is_unclean;
};

template <is_infint N>
struct infclean_i
{
	using result = pair<first<N>, typename infclean_i<second<N>>::result>;
};

template <is_number N>
using infclean_t = typename infclean_i<N>::result;

using infclean_f = unary<infclean_t>;

template <typename N = noarg>
using infclean = apply<infclean_f, N>;

template <is_infint_unclean N>
struct infclean_i<N>
{
	using result = inf0;
};

// impl nil

template <>
struct nil_traits<inf0>
{
	static constexpr bool is_nil = true;
};

// impl natural

template <>
struct natural_traits<inf0>
{
	static constexpr bool is_natural = true;
	static constexpr bool is_zero = true;
	static constexpr unsigned long long value = 0;
};

template <is_list_pair N>
	requires is_bool<first<N>> && is_infint<second<N>>
struct natural_traits<N>
{
	static constexpr bool is_natural = true;
	static constexpr bool is_zero = false;
	static constexpr auto value = static_cast<unsigned long long>(is_true<first<N>>) | (number_value<second<N>> << 1);
};

template <is_infint N, is_bool Carry = True>
struct infsucc_i
{
	using n = first<N>;
	using result = pair<Xor<n, Carry>, typename infsucc_i<second<N>, And<n, Carry>>::result>;
};

template <is_infint N>
struct succ_i<N>
{
	using result = typename infsucc_i<N>::result;
};

template <>
struct infsucc_i<inf0, False>
{
	using result = inf0;
};

template <>
struct infsucc_i<inf0, True>
{
	using result = inf1;
};

template <is_infint N, is_bool Carry = False>
struct infprev_i
{
	using n = first<N>;
	using xnt = Xor<n, True>;
	using axc = And<xnt, Carry>;
	using ant = And<n, True>;
	using carry = Or<axc, ant>;
	using xxc = Xor<xnt, Carry>;
	using result = pair<xxc, typename infprev_i<second<N>, carry>::result>;
};

template <is_infint N>
struct prev_i<N>
{
	using result = infclean<typename infprev_i<N>::result>;
};

template <is_bool Bool>
struct infprev_i<inf0, Bool>
{
	using result = inf0;
};

template <is_infint N>
struct zero_i<N>
{
	using result = inf0;
};

template <is_infint Lhs, is_infint Rhs, is_bool Carry = False>
struct infadd_i
{
	using lhs = first<Lhs>;
	using rhs = first<Rhs>;
	using xlr = Xor<lhs, rhs>;
	using axc = And<xlr, Carry>;
	using alr = And<lhs, rhs>;
	using carry = Or<axc, alr>;
	using xxc = Xor<xlr, Carry>;
	using result = pair<xxc, typename infadd_i<second<Lhs>, second<Rhs>, carry>::result>;
};

template <is_infint Lhs, is_infint Rhs>
struct add_i<Lhs, Rhs>
{
	using result = typename infadd_i<Lhs, Rhs>::result;
};

template <is_infint N>
	requires is_strict_positive<N>
struct infadd_i<inf0, N, False>
{
	using result = N;
};

template <is_infint N>
	requires is_strict_positive<N>
struct infadd_i<inf0, N, True>
{
	using result = succ<N>;
};

template <is_infint N>
struct infadd_i<N, inf0, False>
{
	using result = N;
};

template <is_infint N>
struct infadd_i<N, inf0, True>
{
	using result = succ<N>;
};

using inf2 = succ<inf1>;
using inf3 = succ<inf2>;
using inf4 = succ<inf3>;
using inf5 = succ<inf4>;
using inf6 = succ<inf5>;
using inf7 = succ<inf6>;
using inf8 = succ<inf7>;
using inf9 = succ<inf8>;
using inf10 = succ<inf9>;

template <size_t N>
struct inf_i
{
	using result = pair<Bool<N % 2 != 0>, typename inf_i<N / 2>::result>;
};

template <size_t N>
using inf = typename inf_i<N>::result;

template <>
struct inf_i<0>
{
	using result = inf0;
};

} // namespace functional
