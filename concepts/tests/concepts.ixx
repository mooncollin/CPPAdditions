export module cmoon.tests.concepts;

import std.core;

import cmoon.test;
import cmoon.concepts;

namespace cmoon::tests::concepts
{
	export
	class function_object_test : public cmoon::test::test_case
	{
		public:
			function_object_test()
				: cmoon::test::test_case{"function_object_test"} {}

			void operator()() override
			{
				struct s { void operator()() {} };
				struct s2 { void operator()(int) {} };

				cmoon::test::assert_true(cmoon::function_object<s>);
				cmoon::test::assert_true(cmoon::function_object<s2, int>);
				cmoon::test::assert_true(cmoon::function_object<decltype([]{})>);

				cmoon::test::assert_false(cmoon::function_object<s2>);
				cmoon::test::assert_false(cmoon::function_object<void()>);
			}
	};

	export
	class complete_type_test : public cmoon::test::test_case
	{
		public:
			complete_type_test()
				: cmoon::test::test_case{"complete_type_test"} {}

			void operator()() override
			{
				class f;
				
				cmoon::test::assert_true(cmoon::complete_type<int>);
				cmoon::test::assert_true(cmoon::complete_type<double>);
				cmoon::test::assert_true(cmoon::complete_type<const int>);
				cmoon::test::assert_true(cmoon::complete_type<const double>);
				cmoon::test::assert_true(cmoon::complete_type<std::string>);
				cmoon::test::assert_true(cmoon::complete_type<const std::string>);

				cmoon::test::assert_true(cmoon::complete_type<int&>);
				cmoon::test::assert_true(cmoon::complete_type<double&>);
				cmoon::test::assert_true(cmoon::complete_type<const int&>);
				cmoon::test::assert_true(cmoon::complete_type<const double&>);
				cmoon::test::assert_true(cmoon::complete_type<std::string&>);
				cmoon::test::assert_true(cmoon::complete_type<const std::string&>);

				cmoon::test::assert_false(cmoon::complete_type<f>);
			}
	};

	export
	class has_type_test : public cmoon::test::test_case
	{
		public:
			has_type_test()
				: cmoon::test::test_case{"has_type_test"} {}

			void operator()() override
			{
				cmoon::test::assert_true(cmoon::has_type<std::type_identity<int>>);
				cmoon::test::assert_false(cmoon::has_type<int>);
			}
	};

	export
	class stream_writable_test : public cmoon::test::test_case
	{
		public:
			stream_writable_test()
				: cmoon::test::test_case{"stream_writable_test"} {}

			void operator()() override
			{
				struct s {};

				cmoon::test::assert_true(cmoon::stream_writable<std::string, std::ostream>);
				cmoon::test::assert_false(cmoon::stream_writable<s, std::ostream>);
			}
	};

	export
	class string_literal_test : public cmoon::test::test_case
	{
		public:
			string_literal_test()
				: cmoon::test::test_case{"string_literal_test"} {}

			void operator()() override
			{
				const char s1[] = "Hello!";
				const auto s2 = std::string{"Hello!"};

				cmoon::test::assert_true(cmoon::string_literal<decltype(s1)>);
				cmoon::test::assert_false(cmoon::string_literal<decltype(s2)>);
			}
	};

	export
	class character_test : public cmoon::test::test_case
	{
		public:
			character_test()
				: cmoon::test::test_case{"character_test"} {}

			void operator()() override
			{
				cmoon::test::assert_true(cmoon::character<char>);
				cmoon::test::assert_true(cmoon::character<unsigned char>);
				cmoon::test::assert_true(cmoon::character<const char>);
				cmoon::test::assert_true(cmoon::character<const unsigned char>);
				cmoon::test::assert_true(cmoon::character<signed char>);
				cmoon::test::assert_true(cmoon::character<const signed char>);
				cmoon::test::assert_true(cmoon::character<wchar_t>);
				cmoon::test::assert_true(cmoon::character<const wchar_t>);
				cmoon::test::assert_true(cmoon::character<char16_t>);
				cmoon::test::assert_true(cmoon::character<const char16_t>);
				cmoon::test::assert_true(cmoon::character<char32_t>);
				cmoon::test::assert_true(cmoon::character<const char32_t>);
				cmoon::test::assert_true(cmoon::character<char8_t>);
				cmoon::test::assert_true(cmoon::character<const char8_t>);
				cmoon::test::assert_true(cmoon::character<int>);
				cmoon::test::assert_true(cmoon::character<const int>);

				cmoon::test::assert_false(cmoon::character<bool>);
				cmoon::test::assert_false(cmoon::character<short>);
				cmoon::test::assert_false(cmoon::character<long>);
				cmoon::test::assert_false(cmoon::character<double>);
			}
	};

	export
	class formattable_test : public cmoon::test::test_case
	{
		public:
			formattable_test()
				: cmoon::test::test_case{"formattable_test"} {}

			void operator()() override
			{
				struct s {};

				cmoon::test::assert_true(cmoon::formattable<bool>);
				cmoon::test::assert_true(cmoon::formattable<short>);
				cmoon::test::assert_true(cmoon::formattable<int>);
				cmoon::test::assert_true(cmoon::formattable<long>);
				cmoon::test::assert_true(cmoon::formattable<double>);
				cmoon::test::assert_true(cmoon::formattable<std::string>);
				cmoon::test::assert_true(cmoon::formattable<std::string_view>);

				cmoon::test::assert_false(cmoon::formattable<s>);
			}
	};

	export
	class specialization_of_test : public cmoon::test::test_case
	{
		public:
			specialization_of_test()
				: cmoon::test::test_case{"specialization_of_test"} {}

			void operator()() override
			{
				cmoon::test::assert_true(cmoon::specialization_of<std::string, std::basic_string>);

				cmoon::test::assert_false(cmoon::specialization_of<int, std::bool_constant>);
			}
	};

	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Concepts library tests"};
		suite.add_test_case<function_object_test>();
		suite.add_test_case<complete_type_test>();
		suite.add_test_case<has_type_test>();
		suite.add_test_case<stream_writable_test>();
		suite.add_test_case<string_literal_test>();
		suite.add_test_case<character_test>();
		suite.add_test_case<formattable_test>();
		suite.add_test_case<specialization_of_test>();

		return std::move(suite);
	}
}