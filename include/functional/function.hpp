#pragma once

#include <concepts>

namespace functional
{

struct noarg
{};

template <typename T, typename IfTrue, typename IfFalse>
struct ifnoarg_i
{
	using result = IfFalse;
};

template <typename T, typename IfTrue, typename IfFalse>
using ifnoarg = typename ifnoarg_i<T, IfTrue, IfFalse>::result;

template <typename T>
concept is_not_noargs = !std::same_as<T, noarg>;

template <typename IfTrue, typename IfFalse>
struct ifnoarg_i<noarg, IfTrue, IfFalse>
{
	using result = IfTrue;
};

template <template <typename> typename T>
concept is_call = true;

template <typename T>
concept is_function = is_call<T::template result>;

template <typename T>
struct function_traits
{
	static constexpr bool is_function = false;
};

template <typename T>
concept is_unary = is_function<T>;

template <is_function Func, typename Arg, typename... Args>
struct apply_i
{
	using result = typename apply_i<typename Func::template result<Arg>, Args...>::result;
};

template <is_function Func, typename Arg>
struct apply_i<Func, Arg>
{
	using result = typename Func::template result<Arg>;
};

template <is_function Func, typename Arg, typename... Args>
using apply = typename apply_i<Func, Arg, Args...>::result;

template <typename T, typename Arg>
concept is_strict_unary = is_function<T> && !is_function<apply<T, Arg>>;

template <template <typename> typename Call, typename Arg>
struct unary_i
{
	using result = Call<Arg>;
};

template <template <typename> typename Call>
struct unary
{
	template <typename Arg>
	using result = typename unary_i<Call, Arg>::result;
};

template <template <typename> typename Call>
struct unary_i<Call, noarg>
{
	using result = unary<Call>;
};

template <template <typename, typename> typename Call, typename Arg>
struct binary_i
{
	struct impl_
	{
		template <typename Arg1>
		using result = Call<Arg, Arg1>;
	};

	using result = unary<impl_::template result>;
};

template <template <typename, typename> typename Call>
struct binary
{
	template <typename Arg>
	using result = typename binary_i<Call, Arg>::result;
};

template <template <typename, typename> typename Call>
struct binary_i<Call, noarg>
{
	using result = binary<Call>;
};

template <template <typename, typename, typename> typename Call, typename Arg>
struct ternary_i
{
	struct impl_
	{
		template <typename Arg1, typename Arg2>
		using result = Call<Arg, Arg1, Arg2>;
	};

	using result = binary<impl_::template result>;
};

template <template <typename, typename, typename> typename Call>
struct ternary
{
	template <typename Arg>
	using result = typename ternary_i<Call, Arg>::result;
};

template <template <typename, typename, typename> typename Call>
struct ternary_i<Call, noarg>
{
	using result = ternary<Call>;
};

template <template <typename, typename, typename, typename> typename Call, typename Arg>
struct quaternary_i
{
	struct impl_
	{
		template <typename Arg1, typename Arg2, typename Arg3>
		using result = Call<Arg, Arg1, Arg2, Arg3>;
	};

	using result = ternary<impl_::template result>;
};

template <template <typename, typename, typename, typename> typename Call>
struct quaternary
{
	template <typename Arg>
	using result = typename quaternary_i<Call, Arg>::result;
};

template <template <typename, typename, typename, typename> typename Call>
struct quaternary_i<Call, noarg>
{
	using result = quaternary<Call>;
};

template <typename T>
using id_t = T;

using id_f = unary<id_t>;

template <typename T = noarg>
using id = apply<id_f, T>;

template <is_function Func, typename Rhs, typename Lhs>
using binflip_t = apply<Func, Lhs, Rhs>;

using binflip_f = ternary<binflip_t>;

template <typename Func = noarg, typename Lhs = noarg, typename Rhs = noarg>
using binflip = apply<binflip_f, Func, Lhs, Rhs>;

} // namespace functional
