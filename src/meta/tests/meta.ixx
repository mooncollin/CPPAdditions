export module cmoon.tests.meta;
export import :type_list;
export import :value_list;

import std.core;

import cmoon.test;

namespace cmoon::tests::meta
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Meta library tests"};

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

		suite.add_test_case<value_list_size_test>();
		suite.add_test_case<value_list_get_test>();
		suite.add_test_case<value_list_contains_test>();
		suite.add_test_case<value_list_tuple_test>();
		suite.add_test_case<value_list_all_of_test>();
		suite.add_test_case<value_list_any_of_test>();
		suite.add_test_case<value_list_none_of_test>();
		suite.add_test_case<value_list_for_each_test>();
		suite.add_test_case<value_list_append_test>();
		suite.add_test_case<value_list_concatenate_test>();
		suite.add_test_case<value_list_concatenate_test>();
		suite.add_test_case<value_list_filter_test>();
		suite.add_test_case<value_list_transform_test>();
		suite.add_test_case<value_list_transform_to_types_test>();
		suite.add_test_case<value_list_sub_list_test>();
		suite.add_test_case<transform_values_test>();
		suite.add_test_case<filter_values_test>();
		suite.add_test_case<concatenate_values_test>();
		suite.add_test_case<iota_test>();
		suite.add_test_case<index_sequence_test>();
		suite.add_test_case<make_integer_sequence_test>();
		suite.add_test_case<make_index_sequence_test>();
		suite.add_test_case<index_sequence_for_test>();
		suite.add_test_case<gen_value_list_test>();

		return std::move(suite);
	}
}