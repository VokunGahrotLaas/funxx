#pragma once

#include <cstddef>
#include <functional/bool.hpp>
#include <functional/function.hpp>

namespace functional
{

// trait number

template <typename T>
struct natural_traits
{
	static constexpr bool is_natural = false;
	static constexpr bool is_zero = false;
	static constexpr unsigned long long value = 0;
};

template <typename T>
struct integer_traits
{
	static constexpr bool is_integer = false;
	static constexpr bool is_zero = false;
	static constexpr bool is_strict_negative = false;
	static constexpr bool is_strict_positive = false;
	static constexpr long long value = 0;
};

template <typename T>
struct number_traits
{
	static constexpr bool is_number = false;
	static constexpr bool is_zero = false;
	static constexpr bool is_strict_negative = false;
	static constexpr bool is_strict_positive = false;
	static constexpr long long value = 0;
};

template <typename T>
concept is_number = number_traits<T>::is_number;

template <typename T>
concept is_natural_i = natural_traits<T>::is_natural;

template <typename T>
concept is_integer_i = integer_traits<T>::is_integer;

template <typename T>
concept is_natural = is_number<T> && is_natural_i<T>;

template <typename T>
concept is_integer = is_number<T> && is_integer_i<T>;

template <is_number T>
static constexpr auto number_value = number_traits<T>::value;

template <typename T>
concept is_zero = is_number<T> && number_traits<T>::is_zero;

template <typename T>
concept is_strict_negative = is_number<T> && number_traits<T>::is_strict_negative;

template <typename T>
concept is_strict_positive = is_number<T> && number_traits<T>::is_strict_positive;

template <typename T>
concept is_negative = is_number<T> && (is_strict_negative<T> || is_zero<T>);

template <typename T>
concept is_positive = is_number<T> && (is_strict_positive<T> || is_zero<T>);

template <typename T>
concept is_not_zero = is_number<T> && !is_zero<T>;

template <typename T, size_t Value>
concept is_number_value = is_number<T> && number_traits<T>::value == Value;

template <is_natural_i T>
struct number_traits<T>
{
	static constexpr bool is_number = true;
	static constexpr bool is_zero = natural_traits<T>::is_zero;
	static constexpr bool is_strict_negative = false;
	static constexpr bool is_strict_positive = !is_zero;
	static constexpr auto value = natural_traits<T>::value;
};

template <is_integer_i T>
struct number_traits<T>
{
	static constexpr bool is_number = true;
	static constexpr bool is_zero = integer_traits<T>::is_zero;
	static constexpr bool is_strict_negative = integer_traits<T>::is_strict_negative;
	static constexpr bool is_strict_positive = integer_traits<T>::is_strict_positive;
	static constexpr auto value = integer_traits<T>::value;
};

template <is_number>
struct succ_i
{};

template <is_number N>
using succ_t = typename succ_i<N>::result;

using succ_f = unary<succ_t>;

template <typename N = noarg>
using succ = apply<succ_f, N>;

template <is_number>
struct prev_i
{};

template <is_number N>
using prev_t = typename prev_i<N>::result;

using prev_f = unary<prev_t>;

template <typename N = noarg>
using prev = apply<prev_f, N>;

template <is_number>
struct zero_i
{};

template <is_number N>
using zero_t = typename zero_i<N>::result;

using zero_f = unary<zero_t>;

template <typename N = noarg>
using zero = apply<zero_f, N>;

// bonus

template <typename T>
concept is_one = is_number<T> && is_strict_positive<T> && is_zero<prev<T>>;

template <typename T>
concept is_mone = is_number<T> && is_strict_negative<T> && is_zero<succ<T>>;

template <typename T>
concept is_gt_one = is_number<T> && is_positive<T> && !is_zero<T> && !is_one<T>;

template <typename T>
concept is_gt_mone = is_number<T> && is_negative<T> && !is_zero<T> && !is_mone<T>;

template <is_number N>
struct one_i
{
	using result = succ<zero<N>>;
};

template <is_number N>
using one_t = typename one_i<N>::result;

using one_f = unary<one_t>;

template <typename N = noarg>
using one = apply<one_f, N>;

template <is_integer N>
struct mone_i
{
	using result = prev<zero<N>>;
};

template <is_integer N>
using mone_t = typename mone_i<N>::result;

using mone_f = unary<mone_t>;

template <typename N = noarg>
using mone = apply<mone_f, N>;

template <is_function Func, typename Arg, is_positive Count>
struct apply_n_i
{};

template <is_function Func, typename Arg, is_positive Count>
using apply_n_t = typename apply_n_i<Func, Arg, Count>::result;

using apply_n_f = ternary<apply_n_t>;

template <typename Func = noarg, typename Arg = noarg, typename Count = noarg>
using apply_n = apply<apply_n_f, Func, Arg, Count>;

template <is_function Func, typename Arg, is_zero Zero>
struct apply_n_i<Func, Arg, Zero>
{
	using result = Arg;
};

template <is_function Func, typename Arg, is_strict_positive Count>
struct apply_n_i<Func, Arg, Count>
{
	using result = apply_n<Func, apply<Func, Arg>, prev<Count>>;
};

template <is_function Func, typename Arg, is_negative Count>
struct apply_mn_i
{};

template <is_function Func, typename Arg, is_negative Count>
using apply_mn_t = typename apply_mn_i<Func, Arg, Count>::result;

using apply_mn_f = ternary<apply_mn_t>;

template <typename Func = noarg, typename Arg = noarg, typename Count = noarg>
using apply_mn = apply<apply_n_f, Func, Arg, Count>;

template <is_function Func, typename Arg, is_zero Zero>
struct apply_mn_i<Func, Arg, Zero>
{
	using result = Arg;
};

template <is_function Func, typename Arg, is_strict_negative Count>
struct apply_mn_i<Func, Arg, Count>
{
	using result = apply_mn<Func, apply<Func, Arg>, succ<Count>>;
};

template <is_integer N>
struct neg_i
{
	using result = N;
};

template <is_integer N>
using neg_t = typename neg_i<N>::result;

using neg_f = unary<neg_t>;

template <typename N = noarg>
using neg = apply<neg_f, N>;

template <is_integer N>
	requires is_strict_positive<N>
struct neg_i<N>
{
	using result = apply_n<prev<>, zero<N>, N>;
};

template <is_integer N>
	requires is_strict_negative<N>
struct neg_i<N>
{
	using result = apply_mn<succ<>, zero<N>, N>;
};

template <is_number N>
struct abs_i
{
	using result = N;
};

template <is_number N>
using abs_t = typename abs_i<N>::result;

using abs_f = unary<abs_t>;

template <typename N = noarg>
using abs = apply<abs_f, N>;

template <is_strict_negative N>
struct abs_i<N>
{
	using result = neg<N>;
};

template <is_number>
struct sign_i
{
	using result = False;
};

template <is_number N>
using sign_t = typename sign_i<N>::result;

using sign_f = unary<sign_t>;

template <typename N = noarg>
using sign = apply<sign_f, N>;

template <is_strict_negative N>
struct sign_i<N>
{
	using result = True;
};

template <is_bool B, is_number N>
struct ctsign_i
{
	using result = N;
};

template <is_bool B, is_number N>
using ctsign_t = typename ctsign_i<B, N>::result;

using ctsign_f = binary<ctsign_t>;

template <typename B = noarg, typename N = noarg>
using ctsign = apply<ctsign_f, B, N>;

template <is_true B, is_integer N>
struct ctsign_i<B, N>
{
	using result = neg<N>;
};

template <is_true B, is_natural N>
struct ctsign_i<B, N>
{
	static_assert(false);
};

// optional trait number

template <is_number Lhs, is_number Rhs>
struct add_i
{
	using result = apply_n<ifthenelse<Bool<is_positive<Rhs>>, succ<>, prev<>>, Lhs, abs<Rhs>>;
};

template <is_number Lhs, is_number Rhs>
using add_t = typename add_i<Lhs, Rhs>::result;

using add_f = binary<add_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using add = apply<add_f, Lhs, Rhs>;

template <is_number Lhs, is_number Rhs>
struct mul_i
{
	using result = ctsign<sign<Rhs>, apply_n<add<Lhs>, zero<Lhs>, abs<Rhs>>>;
};

template <is_number Lhs, is_number Rhs>
using mul_t = typename mul_i<Lhs, Rhs>::result;

using mul_f = binary<mul_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using mul = apply<mul_f, Lhs, Rhs>;

template <is_number Lhs, is_natural Rhs>
struct pow_i
{
	using result = apply_n<mul<Lhs>, one<Lhs>, Rhs>;
};

template <is_number Lhs, is_natural Rhs>
using pow_t = typename pow_i<Lhs, Rhs>::result;

using pow_f = binary<pow_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using pow = apply<pow_f, Lhs, Rhs>;

template <is_number N>
struct even_i
{
	using result = True;
};

template <is_number N>
using even_t = typename even_i<N>::result;

using even_f = unary<even_t>;

template <typename N = noarg>
using even = apply<even_f, N>;

template <is_strict_negative N>
struct even_i<N>
{
	using result = Not<even<succ<N>>>;
};

template <is_strict_positive N>
struct even_i<N>
{
	using result = Not<even<prev<N>>>;
};

template <is_number N>
struct odd_i
{
	using value = False;
};

template <is_number N>
using odd_t = typename odd_i<N>::result;

using odd_f = unary<odd_t>;

template <typename N = noarg>
using odd = apply<odd_f, N>;

template <is_strict_negative N>
struct odd_i<N>
{
	using result = Not<odd<succ<N>>>;
};

template <is_strict_positive N>
struct odd_i<N>
{
	using result = Not<odd<prev<N>>>;
};

// bonus

template <is_number F0, is_number F1, is_number N>
struct fibo_i
{};

template <is_number F0, is_number F1, is_number N>
using fibo_t = typename fibo_i<F0, F1, N>::result;

template <is_number N>
using fiboz_t = typename fibo_i<zero<N>, one<N>, N>::result;

using fibo_f = ternary<fibo_t>;

using fiboz_f = unary<fiboz_t>;

template <typename F0 = noarg, typename F1 = noarg, typename N = noarg>
using fibo = apply<fibo_f, F0, F1, N>;

template <typename N = noarg>
using fiboz = apply<fiboz_f, N>;

template <is_number F0, is_number F1, is_zero Zero>
struct fibo_i<F0, F1, Zero>
{
	using result = F0;
};

template <is_number F0, is_number F1, is_one One>
struct fibo_i<F0, F1, One>
{
	using result = F1;
};

template <is_number F0, is_number F1, is_gt_one N>
struct fibo_i<F0, F1, N>
{
	using result = add<fibo<F0, F1, prev<prev<N>>>, fibo<F0, F1, prev<N>>>;
};

template <is_number N>
using square_t = mul<N, N>;

using square_f = unary<square_t>;

template <typename N = noarg>
using square = apply<square_f, N>;

} // namespace functional
