#pragma once

namespace functional
{

template <typename Lhs, typename Rhs>
struct is_same
{
	static constexpr bool value = false;
};

template <typename Lhs>
struct is_same<Lhs, Lhs>
{
	static constexpr bool value = true;
};

template <typename Lhs, typename Rhs>
static constexpr bool is_same_v = is_same<Lhs, Rhs>::value;

template <typename Lhs, typename Rhs>
concept same_as = is_same_v<Lhs, Rhs>;

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
concept isarg = !same_as<T, noarg>;

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

template <template <typename...> typename Call, typename Arg>
struct func_i
{};

template <template <typename...> typename Call>
struct func
{
	template <typename Arg>
	using result = typename func_i<Call, Arg>::result;
};

template <template <typename...> typename Call>
struct func_i<Call, noarg>
{
	using result = func<Call>;
};

template <template <typename> typename Call, isarg Arg>
struct func_i<Call, Arg>
{
	using result = Call<Arg>;
};

template <template <typename, typename> typename Call, isarg Arg>
struct func_i<Call, Arg>
{
	struct impl_
	{
		template <typename Arg1>
		using result = Call<Arg, Arg1>;
	};

	using result = func<impl_::template result>;
};

template <template <typename, typename, typename> typename Call, isarg Arg>
struct func_i<Call, Arg>
{
	struct impl_
	{
		template <typename Arg1, typename Arg2>
		using result = Call<Arg, Arg1, Arg2>;
	};

	using result = func<impl_::template result>;
};

template <template <typename, typename, typename, typename> typename Call, isarg Arg>
struct func_i<Call, Arg>
{
	struct impl_
	{
		template <typename Arg1, typename Arg2, typename Arg3>
		using result = Call<Arg, Arg1, Arg2, Arg3>;
	};

	using result = func<impl_::template result>;
};

template <template <typename, typename, typename, typename, typename> typename Call, isarg Arg>
struct func_i<Call, Arg>
{
	struct impl_
	{
		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		using result = Call<Arg, Arg1, Arg2, Arg3, Arg4>;
	};

	using result = func<impl_::template result>;
};

template <typename T>
using id_t = T;

using id_f = func<id_t>;

template <typename T = noarg>
using id = apply<id_f, T>;

template <is_function Func, typename Rhs, typename Lhs>
using binflip_t = apply<Func, Lhs, Rhs>;

using binflip_f = func<binflip_t>;

template <typename Func = noarg, typename Lhs = noarg, typename Rhs = noarg>
using binflip = apply<binflip_f, Func, Lhs, Rhs>;

} // namespace functional
