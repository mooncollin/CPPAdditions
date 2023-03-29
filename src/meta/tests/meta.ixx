export module cmoon.tests.meta;
export import cmoon.tests.meta.type_list;

import std.core;

import cmoon.test;

namespace cmoon::tests::meta
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Meta library tests"};
		suite.add_test_case<type_list_construct_test>();
		suite.add_test_case<type_list_size_test>();
		suite.add_test_case<type_list_empty_test>();
		suite.add_test_case<type_list_type_test>();
		suite.add_test_case<type_list_index_test>();
		suite.add_test_case<type_list_contains_test>();
		suite.add_test_case<type_list_all_of_test>();
		suite.add_test_case<type_list_any_of_test>();
		suite.add_test_case<type_list_none_of_test>();
		suite.add_test_case<type_list_for_each_test>();
		suite.add_test_case<type_list_append_test>();
		suite.add_test_case<type_list_concatenate_test>();
		suite.add_test_case<type_list_filter_test>();
		suite.add_test_case<type_list_transform_test>();
		suite.add_test_case<type_list_sub_list_test>();
		suite.add_test_case<type_list_unique_test>();
		suite.add_test_case<type_list_find_test>();
		return std::move(suite);
	}
}