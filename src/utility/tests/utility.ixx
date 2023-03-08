export module cmoon.tests.utility;

import std.core;

import cmoon.test;

namespace cmoon::tests::utility
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Utility library tests"};

		return std::move(suite);
	}
}