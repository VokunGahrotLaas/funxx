#pragma once

#include <functional/bool.hpp>
#include <functional/function.hpp>
#include <functional/nil.hpp>
#include <functional/number.hpp>
#include <functional/pair.hpp>

namespace functional
{

template <typename T>
struct list_traits
{
	static constexpr bool is_list = false;
};

template <typename T>
concept is_list = list_traits<T>::is_list;

template <typename T>
concept is_list_nil = is_list<T> && is_nil<T>;

template <typename T>
concept is_list_pair = is_list<T> && is_pair<T>;

template <is_nil Nil>
struct list_traits<Nil>
{
	static constexpr bool is_list = true;
	static constexpr size_type size = 0;
};

template <is_pair Pair>
	requires is_list<second<Pair>>
struct list_traits<Pair>
{
	static constexpr bool is_list = true;
	static constexpr size_type size = list_traits<second<Pair>>::size + 1;
};

template <is_list N>
static constexpr size_type list_size = list_traits<N>::size;

template <typename... Args>
struct list_i
{};

template <typename... Args>
using list = typename list_i<Args...>::result;

template <typename Arg, typename... Args>
struct list_i<Arg, Args...>
{
	using result = pair<Arg, list<Args...>>;
};

template <>
struct list_i<>
{
	using result = nil;
};

template <is_natural Count, is_number Begin>
struct iota_i
{};

template <is_natural Count, is_number Begin>
using iota_t = typename iota_i<Count, Begin>::result;

template <is_natural Count>
using iotaz_t = typename iota_i<Count, zero<Count>>::result;

using iota_f = func<iota_t>;

using iotaz_f = func<iotaz_t>;

template <typename Count = noarg, typename Begin = noarg>
using iota = apply<iota_f, Count, Begin>;

template <typename Count = noarg>
using iotaz = apply<iota_f, Count, ifnoarg<Count, noarg, zero<Count>>>;

template <is_zero Zero, is_number Begin>
	requires is_natural<Zero>
struct iota_i<Zero, Begin>
{
	using result = nil;
};

template <is_strict_positive Count, is_number Begin>
	requires is_natural<Count>
struct iota_i<Count, Begin>
{
	using result = pair<Begin, iota<prev<Count>, succ<Begin>>>;
};

template <is_function Func, typename Acc, is_list List>
struct foldr_i
{};

template <is_function Func, typename Acc, is_list List>
using foldr_t = typename foldr_i<Func, Acc, List>::result;

using foldr_f = func<foldr_t>;

template <typename Func = noarg, typename Acc = noarg, typename List = noarg>
using foldr = apply<foldr_f, Func, Acc, List>;

template <is_function Func, typename Acc, is_list_nil Nil>
struct foldr_i<Func, Acc, Nil>
{
	using result = Acc;
};

template <is_function Func, typename Acc, is_list_pair Pair>
struct foldr_i<Func, Acc, Pair>
{
	using result = apply<Func, first<Pair>, foldr<Func, Acc, second<Pair>>>;
};

template <is_function Func, typename Acc, is_list List>
struct foldl_i
{};

template <is_function Func, typename Acc, is_list List>
using foldl_t = typename foldl_i<Func, Acc, List>::result;

using foldl_f = func<foldl_t>;

template <typename Func = noarg, typename Acc = noarg, typename List = noarg>
using foldl = apply<foldl_f, Func, Acc, List>;

template <is_function Func, typename Acc, is_list_nil Nil>
struct foldl_i<Func, Acc, Nil>
{
	using result = Acc;
};

template <is_function Func, typename Acc, is_list_pair Pair>
struct foldl_i<Func, Acc, Pair>
{
	using result = foldl<Func, apply<Func, Acc, first<Pair>>, second<Pair>>;
};

template <is_function Func, is_list List>
struct map_i
{};

template <is_function Func, is_list List>
using map_t = typename map_i<Func, List>::result;

using map_f = func<map_t>;

template <typename Func = noarg, typename List = noarg>
using map = apply<map_f, Func, List>;

template <is_function Func, is_list_nil Nil>
struct map_i<Func, Nil>
{
	using result = nil;
};

template <is_function Func, is_list_pair Pair>
struct map_i<Func, Pair>
{
	using result = pair<apply<Func, first<Pair>>, map<Func, second<Pair>>>;
};

template <is_natural Index, is_list List>
struct get_i
{};

template <is_number Index, is_list List>
using get_t = typename get_i<Index, List>::result;

using get_f = func<get_t>;

template <typename Index = noarg, typename List = noarg>
using get = apply<get_f, Index, List>;

template <is_zero Zero, is_list List>
	requires is_natural<Zero>
struct get_i<Zero, List>
{
	using result = first<List>;
};

template <is_strict_positive Index, is_list List>
	requires is_natural<Index>
struct get_i<Index, List>
{
	using result = get<prev<Index>, second<List>>;
};

template <is_list Lhs, is_list Rhs>
struct zip_i
{
	using result = nil;
};

template <is_list Lhs, is_list Rhs>
using zip_t = typename zip_i<Lhs, Rhs>::result;

using zip_f = func<zip_t>;

template <typename Lhs = noarg, typename Rhs = noarg>
using zip = apply<zip_f, Lhs, Rhs>;

template <is_list_pair Lhs, is_list_pair Rhs>
struct zip_i<Lhs, Rhs>
{
	using result = pair<pair<first<Lhs>, first<Rhs>>, zip<second<Lhs>, second<Rhs>>>;
};

template <is_number F0, is_number F1, is_number N>
using fibos = map<fibo<F0, F1>, iotaz<N>>;

template <is_number N>
using fibozs = map<fiboz<>, iotaz<N>>;

template <is_function Pred, is_list List>
struct filter_i
{};

template <is_function Pred, is_list List>
using filter_t = typename filter_i<Pred, List>::result;

using filter_f = func<filter_t>;

template <typename Pred = noarg, typename List = noarg>
using filter = apply<filter_f, Pred, List>;

template <is_function Pred, is_list_nil Nil>
struct filter_i<Pred, Nil>
{
	using result = nil;
};

template <is_function Pred, is_list_pair Pair>
struct filter_i<Pred, Pair>
{
	using next = filter<Pred, second<Pair>>;
	using result = ifthenelse<apply<Pred, first<Pair>>, pair<first<Pair>, next>, next>;
};

template <is_natural Count, is_list List>
struct take_i
{
	using result = nil;
};

template <is_natural Count, is_list List>
using take_t = typename take_i<Count, List>::result;

using take_f = func<take_t>;

template <typename Count, typename List>
using take = apply<take_f, Count, List>;

template <is_strict_positive Count, is_list_pair List>
	requires is_natural<Count>
struct take_i<Count, List>
{
	using result = pair<first<List>, take<prev<Count>, second<List>>>;
};

template <is_natural Count, is_list List>
struct drop_i
{
	using result = nil;
};

template <is_natural Count, is_list List>
using drop_t = typename drop_i<Count, List>::result;

using drop_f = func<drop_t>;

template <typename Count, typename List>
using drop = apply<drop_f, Count, List>;

template <is_strict_positive Count, is_list_pair List>
	requires is_natural<Count>
struct drop_i<Count, List>
{
	using result = drop<prev<Count>, second<List>>;
};

template <is_zero Count, is_list_pair List>
	requires is_natural<Count>
struct drop_i<Count, List>
{
	using result = List;
};

} // namespace functional
