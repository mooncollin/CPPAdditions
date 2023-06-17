export module cmoon.tests.string;
export import :algorithm;

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
		return std::move(suite);
	}
}