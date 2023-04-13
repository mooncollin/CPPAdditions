export module cmoon.tests.named_tuple;

import std.core;

import cmoon.named_tuple;
import cmoon.test;

namespace cmoon::tests::named_tuple
{
	export
    class default_constructor_test : public cmoon::test::test_case
    {
        public:
            default_constructor_test()
                : cmoon::test::test_case{"default_constructor_test"} {}

            void operator()() final
            {
				constexpr cmoon::named_tuple<int, float, char> t;
			}
    };

	export
    class constructor_test : public cmoon::test::test_case
    {
        public:
            constructor_test()
                : cmoon::test::test_case{"constructor_test"} {}

            void operator()() final
            {
				constexpr cmoon::named_tuple<int, float, char> t {
					55,
					4.0f,
					'c'
				};
			}
    };

	export
    class get_test : public cmoon::test::test_case
    {
        public:
            get_test()
                : cmoon::test::test_case{"get_test"} {}

            void operator()() final
            {
				constexpr cmoon::named_tuple<int, float, char> t {
					55,
					4.0f,
					'c'
				};

				cmoon::named_tuple<int, float, char> t2 {
					55,
					4.0f,
					'c'
				};

				cmoon::test::assert_equal(t.get<int>(), 55);
				cmoon::test::assert_equal(t.get<float>(), 4.0f);
				cmoon::test::assert_equal(t.get<char>(), 'c');

				cmoon::test::assert_equal(std::get<int>(t), 55);
				cmoon::test::assert_equal(std::get<float>(t), 4.0f);
				cmoon::test::assert_equal(std::get<char>(t), 'c');

				t2.get<int>() = 10;
				t2.get<float>() = 5.5f;
				t2.get<char>() = 'a';

				cmoon::test::assert_equal(t2.get<int>(), 10);
				cmoon::test::assert_equal(t2.get<float>(), 5.5f);
				cmoon::test::assert_equal(t2.get<char>(), 'a');

				std::get<int>(t2) = std::get<int>(t);
				std::get<float>(t2) = std::get<float>(t);
				std::get<char>(t2) = std::get<char>(t);

				cmoon::test::assert_equal(std::get<int>(t2), 55);
				cmoon::test::assert_equal(std::get<float>(t2), 4.0f);
				cmoon::test::assert_equal(std::get<char>(t2), 'c');
			}
    };

	export
    class copy_constructor_test : public cmoon::test::test_case
    {
        public:
            copy_constructor_test()
                : cmoon::test::test_case{"copy_constructor_test"} {}

            void operator()() final
            {
				constexpr cmoon::named_tuple<int, float, char> t {
					55,
					4.0f,
					'c'
				};

				cmoon::named_tuple<int, float, char> t2 {t};

				cmoon::test::assert_equal(t2.get<int>(), 55);
				cmoon::test::assert_equal(t2.get<float>(), 4.0f);
				cmoon::test::assert_equal(t2.get<char>(), 'c');
			}
    };

	export
    class has_attr_test : public cmoon::test::test_case
    {
        public:
            has_attr_test()
                : cmoon::test::test_case{"has_attr_test"} {}

            void operator()() final
            {
				constexpr cmoon::named_tuple<int, float, char> t {
					55,
					4.0f,
					'c'
				};

				cmoon::test::assert_true(t.has_attr<int>());
				cmoon::test::assert_true(t.has_attr<float>());
				cmoon::test::assert_true(t.has_attr<char>());
				cmoon::test::assert_false(t.has_attr<std::string>());
				cmoon::test::assert_false(t.has_attr<int*>());
				cmoon::test::assert_false(t.has_attr<const int>());
			}
    };

	export
    class values_test : public cmoon::test::test_case
    {
        public:
            values_test()
                : cmoon::test::test_case{"values_test"} {}

            void operator()() final
            {
				cmoon::named_tuple t {
					std::string{"Hello"}
				};

				auto tuple1 = t.values();

				cmoon::test::assert_equal(std::get<0>(tuple1), "Hello");
				cmoon::test::assert_equal(std::get<std::string>(t), "Hello");

				auto tuple2 = std::move(t).values();
				cmoon::test::assert_equal(std::get<0>(tuple1), "Hello");
				cmoon::test::assert_equal(std::get<std::string>(t), "");
			}
    };

	export
    class combine_test : public cmoon::test::test_case
    {
        public:
            combine_test()
                : cmoon::test::test_case{"combine_test"} {}

            void operator()() final
            {
				cmoon::named_tuple<int> t1 {5};
				cmoon::named_tuple<double> t2 {1.4};

				auto t3 {t1.combine(t2)};
				cmoon::test::assert_is_type<decltype(t3), cmoon::named_tuple<int, double>>();

				cmoon::test::assert_equal(t3.get<int>(), 5);
				cmoon::test::assert_equal(t3.get<double>(), 1.4);

				cmoon::named_tuple<std::string> t4 {"Hello!"};

				auto t5 {t1.combine(t2, std::move(t4), t2)};

				cmoon::test::assert_is_type<decltype(t5), cmoon::named_tuple<int, double, std::string>>();

				cmoon::test::assert_equal(t5.get<int>(), 5);
				cmoon::test::assert_equal(t5.get<double>(), 1.4);
				cmoon::test::assert_equal(t5.get<std::string>(), "Hello!");

				cmoon::test::assert_equal(t4.get<std::string>(), "");
			}
    };

	export
    class no_ordering_constructor_test : public cmoon::test::test_case
    {
        public:
            no_ordering_constructor_test()
                : cmoon::test::test_case{"no_ordering_constructor_test"} {}

            void operator()() final
            {
				std::string s{"Hello!"};
				cmoon::named_tuple<int, std::string, double> t {
					cmoon::no_ordering,
					std::move(s),
					double{4.5},
					int{5}
				};

				cmoon::test::assert_equal(t.get<int>(), 5);
				cmoon::test::assert_equal(t.get<std::string>(), "Hello!");
				cmoon::test::assert_equal(t.get<double>(), 4.5);

				cmoon::test::assert_equal(s, "");
			}
    };

    export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"named_tuple library tests"};
		suite.add_test_case<default_constructor_test>();
		suite.add_test_case<constructor_test>();
		suite.add_test_case<get_test>();
		suite.add_test_case<copy_constructor_test>();
		suite.add_test_case<has_attr_test>();
		suite.add_test_case<values_test>();
		suite.add_test_case<combine_test>();
		suite.add_test_case<no_ordering_constructor_test>();
		return std::move(suite);
	}
}