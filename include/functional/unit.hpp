#pragma once

namespace functional
{

struct unit
{};

template <typename T>
struct unit_traits
{
	static constexpr bool is_unit = false;
};

template <typename T>
concept is_unit = unit_traits<T>::is_unit;

template <>
struct unit_traits<unit>
{
	static constexpr bool is_unit = true;
};

} // namespace functional
