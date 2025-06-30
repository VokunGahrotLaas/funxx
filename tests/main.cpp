// fun++
#include <functional/functional.hpp>

using namespace functional;

static_assert(is_number_value<n0, 0>);
static_assert(is_number_value<n1, 1>);
static_assert(is_number_value<n2, 2>);
static_assert(is_number_value<n3, 3>);
static_assert(is_number_value<n4, 4>);
static_assert(is_number_value<n5, 5>);
static_assert(is_number_value<n6, 6>);
static_assert(is_number_value<n7, 7>);
static_assert(is_number_value<n8, 8>);
static_assert(is_number_value<n9, 9>);
static_assert(is_number_value<n10, 10>);
static_assert(is_function<succ_f>);
static_assert(is_number<succ_f::result<n0>>);
static_assert(is_number<succ<n0>>);
static_assert(is_function<add_f>);
static_assert(is_function<add<>>);
static_assert(is_function<add<n0>>);
static_assert(is_number<add<n0, n1>>);
static_assert(is_function<id<>>);
static_assert(is_function<id<id_f>>);
static_assert(same_as<id_f, id<>>);
static_assert(same_as<binflip_f, binflip<>>);
static_assert(same_as<apply<binflip_f, add_f>, binflip<add<>>>);
static_assert(same_as<add<n0, n0>, n0>);
static_assert(same_as<add<n0, n1>, n1>);
static_assert(same_as<add<n1, n0>, n1>);
static_assert(same_as<add<n3, n2>, n5>);
static_assert(same_as<mul<n0, n0>, n0>);
static_assert(same_as<mul<n0, n1>, n0>);
static_assert(same_as<mul<n1, n0>, n0>);
static_assert(same_as<mul<n3, n2>, n6>);
static_assert(same_as<pow<n0, n0>, n1>);
static_assert(same_as<pow<n0, n1>, n0>);
static_assert(same_as<pow<n1, n0>, n1>);
static_assert(same_as<pow<n3, n2>, n9>);
static_assert(same_as<iotaz<n2>, list<n0, n1>>);
static_assert(same_as<foldr<add_f, n0, iotaz<n3>>, n3>);
static_assert(same_as<filter<even_f, iotaz<n3>>, list<n0, n2>>);
static_assert(same_as<fibozs<n6>, list<n0, n1, n1, n2, n3, n5>>);
static_assert(same_as<get<n5, fibozs<n6>>, n5>);
// static_assert(same_as<fiboz<nthi<20>>, nthi<6'765ull>>); // crashes
static_assert(same_as<fiboz<uint<20>>, uint<6'765ull>>);
static_assert(same_as<inf0, inf<0>>);
static_assert(same_as<inf1, inf<1>>);
static_assert(same_as<inf10, inf<10>>);
static_assert(number_value<inf<10>> == 10);
static_assert(number_value<inf<20>> == 20);
static_assert(number_value<inf<6'765ull>> == 6'765ull);
static_assert(same_as<add<inf0, inf0>, inf0>);
static_assert(same_as<add<inf0, inf1>, inf1>);
static_assert(same_as<add<inf1, inf0>, inf1>);
static_assert(same_as<add<inf3, inf2>, inf5>);
static_assert(same_as<fiboz<inf<20>>, inf<6'765ull>>);
static_assert(
	same_as<zip<iotaz<n4>, map<square<>, iotaz<n5>>>, list<pair<n0, n0>, pair<n1, n1>, pair<n2, n4>, pair<n3, n9>>>);
static_assert(same_as<map<pair<n0>, iotaz<n2>>, list<pair<n0, n0>, pair<n0, n1>>>);
static_assert(same_as<map<add<n1>, iotaz<n10>>, iota<n10, n1>>);
static_assert(same_as<take<n2, iotaz<n4>>, iotaz<n2>>);
static_assert(same_as<take<n2, nil>, nil>);
static_assert(same_as<drop<n2, iotaz<n4>>, iota<n2, n2>>);
static_assert(same_as<drop<n2, nil>, nil>);
// static_assert(is_number<fiboz<nthu<100>>>); // crashes
static_assert(is_number<fiboz<uint<100>>>); // finished fast but with wrong answer
// static_assert(is_number<fiboz<inf<100>>>); // can finish with right answer

int main() { return 0; }
