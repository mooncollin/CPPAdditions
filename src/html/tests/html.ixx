export module cmoon.tests.html;
export import :attributes;
export import :static_attributes;
export import :element;

import std.core;

import cmoon.test;

namespace cmoon::tests::html
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Html library tests"};
        suite.add_test_case<attributes_accesskey_test>();
		suite.add_test_case<attributes_async_test>();

		suite.add_test_case<static_attributes_constructor_test>();
		suite.add_test_case<static_attributes_get_test>();
		suite.add_test_case<static_attributes_print_test>();

		suite.add_test_case<element_constructor_test>();
		suite.add_test_case<element_print_test>();
		return std::move(suite);
	}
}