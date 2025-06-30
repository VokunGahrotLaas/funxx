// fun++
#include <functional/print.hpp>

using namespace functional;
namespace fun = ::functional;

int main()
{
	std::cout << printer<map<fact<>, iotaz<fun::uint<22>>>>{} << std::endl;
	std::cout << printer<map<fact<>, iotaz<inf<22>>>>{} << std::endl;
	std::cout << printer<inf<0x123456789abcdef>>{} << std::endl;
	std::cout << printer<pair<True, pair<nil, unit>>>{} << std::endl;
	std::cout << printer<fact<>>{} << std::endl;
	std::cout << printer<add<>>{} << std::endl;
	return 0;
}
