#pragma once

#include <concepts>
#include <cstddef>
#include <functional/bool.hpp>
#include <functional/function.hpp>

namespace functional
{

template <typename T>
struct number_traits
{
	static constexpr bool is_number = false;
	static constexpr size_t value = -1;
};

template <typename T>
concept is_number = number_traits<T>::is_number;

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

template <is_number N>
static constexpr size_t number_value = number_traits<N>::value;

template <typename T, size_t Value>
concept is_number_value = is_number<T> && number_traits<T>::value == Value;

template <typename T>
concept is_zero = is_number<T> && std::same_as<prev<T>, T>;

template <typename T>
concept is_gt_zero = is_number<T> && !is_zero<T>;

template <typename T>
concept is_one = is_number<T> && !is_zero<T> && is_zero<prev<T>>;

template <typename T>
concept is_gt_one = is_number<T> && !is_zero<T> && !is_one<T>;

template <is_function Func, is_number Arg, is_number Count>
struct apply_n_i
{};

template <is_function Func, is_number Arg, is_number Count>
using apply_n_t = typename apply_n_i<Func, Arg, Count>::result;

using apply_n_f = ternary<apply_n_t>;

template <typename Func = noarg, typename Arg = noarg, typename Count = noarg>
using apply_n = apply<apply_n_f, Func, Arg, Count>;

template <is_function Func, is_number Arg, is_zero Zero>
struct apply_n_i<Func, Arg, Zero>
{
	using result = Arg;
};

template <is_function Func, is_number Arg, is_gt_zero Count>
struct apply_n_i<Func, Arg, Count>
{
	using result = apply_n<Func, apply<Func, Arg>, prev<Count>>;
};

// optional trait number

template <is_number Lhs, is_number Rhs>
struct add_i
{
	using result = apply_n<succ_f, Lhs, Rhs>;
};

template <is_number Lhs, is_number Rhs>
using add_t = typename add_i<Lhs, Rhs>::result;

using add_f = binary<add_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using add = apply<add_f, Lhs, Rhs>;

template <is_number Lhs, is_number Rhs>
struct mul_i
{
	using result = ifthenelse<Bool<is_zero<Rhs>>, Rhs, apply_n<add<Lhs>, Lhs, prev<Rhs>>>;
};

template <is_number Lhs, is_number Rhs>
using mul_t = typename mul_i<Lhs, Rhs>::result;

using mul_f = binary<mul_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using mul = apply<mul_f, Lhs, Rhs>;

template <is_number Lhs, is_number Rhs>
struct pow_i
{
	using result = ifthenelse<Bool<is_zero<Rhs>>, succ<Rhs>, apply_n<mul<Lhs>, Lhs, prev<Rhs>>>;
};

template <is_number Lhs, is_number Rhs>
using pow_t = typename pow_i<Lhs, Rhs>::result;

using pow_f = binary<pow_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using pow = apply<pow_f, Lhs, Rhs>;

template <is_number N>
struct even_i
{
	using result = Not<typename even_i<prev<N>>::result>;
};

template <is_number N>
using even_t = typename even_i<N>::result;

using even_f = unary<even_t>;

template <typename N = noarg>
using even = apply<even_f, N>;

template <is_zero Zero>
struct even_i<Zero>
{
	using result = True;
};

template <is_number N>
struct odd_i
{
	using value = Not<typename odd_i<prev<N>>::result>;
};

template <is_number N>
using odd_t = typename odd_i<N>::result;

using odd_f = unary<odd_t>;

template <typename N = noarg>
using odd = apply<odd_f, N>;

template <is_zero Zero>
struct odd_i<Zero>
{
	using result = False;
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
