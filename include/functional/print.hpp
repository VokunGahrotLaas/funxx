// C++ STL
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

// fun++
#include <functional/functional.hpp>

namespace functional
{

using u8_t = std::uint8_t;

template <typename T>
struct printer_i
{
	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, struct printer_i<U> const&);
};

using printer_f = func<printer_i>;

template <typename T = noarg>
using printer = apply<printer_f, T>;

template <>
struct printer_i<True>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "true"; }
};

template <>
struct printer_i<unit>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "()"; }
};

template <>
struct printer_i<False>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "false"; }
};

template <>
struct printer_i<nil>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "nil"; }
};

template <is_number T>
	requires(!is_infint<T>)
struct printer_i<T>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&)
	{
		return os << "0x" << std::hex << number_traits<T>::value << std::dec;
	}
};

template <>
struct printer_i<inf0>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "0x0"; }
};

template <is_pair T>
	requires(!is_list<T>)
struct printer_i<T>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&)
	{
		return os << "(" << printer<first<T>>{} << ", " << printer<second<T>>{} << ")";
	}
};

template <is_infint T>
	requires(is_list_pair<T>)
struct printer_i<T>
{
	static std::ostream& print_rec(std::ostream& os, std::vector<u8_t>& d, std::vector<u8_t> v)
	{
		if constexpr (is_true<first<T>>)
			v.push_back(true);
		else
			v.push_back(false);
		if constexpr (!is_nil<second<T>>)
		{
			if (v.size() == 8)
			{
				u8_t u = 0 | ((u8_t)v[0] << 0) | ((u8_t)v[1] << 1) | ((u8_t)v[2] << 2) | ((u8_t)v[3] << 3)
					| ((u8_t)v[4] << 4) | ((u8_t)v[5] << 5) | ((u8_t)v[6] << 6) | ((u8_t)v[7] << 7);
				d.push_back(u);
				v.clear();
			}
			printer<second<T>>::print_rec(os, d, v);
		}
		else
		{
			while (v.size() < 8)
				v.push_back(false);
			u8_t u = 0 | ((u8_t)v[0] << 0) | ((u8_t)v[1] << 1) | ((u8_t)v[2] << 2) | ((u8_t)v[3] << 3)
				| ((u8_t)v[4] << 4) | ((u8_t)v[5] << 5) | ((u8_t)v[6] << 6) | ((u8_t)v[7] << 7);
			d.push_back(u);
		}
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&)
	{
		std::vector<u8_t> d;
		print_rec(os, d, {});
		os << "0x" << std::hex << (unsigned)d.back() << std::dec;
		for (auto u: d | std::views::reverse | std::views::drop(1))
			os << std::hex << std::setw(2) << std::setfill('0') << (unsigned)u << std::dec;
		return os;
	}
};

template <is_list T>
	requires(!is_number<T>)
struct printer_i<T>
{
	static std::ostream& print_rec(std::ostream& os)
	{
		os << printer<typename T::first>{};
		if constexpr (!is_nil<typename T::second>)
		{
			os << ", ";
			printer<typename T::second>::print_rec(os);
		}
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&)
	{
		os << "{";
		print_rec(os);
		os << "}";
		return os;
	}
};

template <template <typename> typename T>
struct printer_i<func<T>>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "func<1>"; }
};

template <template <typename, typename> typename T>
struct printer_i<func<T>>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "func<2>"; }
};

template <template <typename, typename, typename> typename T>
struct printer_i<func<T>>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "func<3>"; }
};

template <template <typename, typename, typename, typename> typename T>
struct printer_i<func<T>>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "func<4>"; }
};

template <template <typename, typename, typename, typename, typename> typename T>
struct printer_i<func<T>>
{
	friend std::ostream& operator<<(std::ostream& os, struct printer_i const&) { return os << "func<5>"; }
};

} // namespace functional
