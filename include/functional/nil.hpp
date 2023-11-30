#pragma once

namespace functional
{

struct nil
{};

template <typename T>
struct nil_traits
{
	static constexpr bool is_nil = false;
};

template <typename T>
concept is_nil = nil_traits<T>::is_nil;

template <>
struct nil_traits<nil>
{
	static constexpr bool is_nil = true;
};

} // namespace functional
