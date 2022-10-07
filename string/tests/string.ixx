export module cmoon.tests.string;
export import cmoon.tests.string.algorithm;
export import cmoon.tests.string.number_string;
export import cmoon.tests.string.to_string;

import std.core;

import cmoon.test;

namespace cmoon::tests::string
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"String library tests"};
		suite.add_test_case<uppercase_test>();
		suite.add_test_case<lowercase_test>();
		suite.add_test_case<trim_front_test>();
		suite.add_test_case<trim_back_test>();
		suite.add_test_case<number_string_default_constructor_test>();
		suite.add_test_case<number_string_integer_test>();
		suite.add_test_case<number_string_float_test>();
		suite.add_test_case<to_string_arithmetic_test>();
		suite.add_test_case<to_wstring_arithmetic_test>();
		return std::move(suite);
	}
}