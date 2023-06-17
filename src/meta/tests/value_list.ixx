export module cmoon.tests.meta:value_list;

import std.core;

import cmoon.test;
import cmoon.meta;

namespace cmoon::tests::meta
{
    export
    class value_list_size_test : public cmoon::test::test_case
    {
        public:
            value_list_size_test()
                : cmoon::test::test_case{"value_list_size_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<>;
                using l2 = cmoon::meta::value_list<5>;
                using l3 = cmoon::meta::value_list<5, 'c', 4.2, 0>;

                cmoon::test::assert_equal(l1::size(), 0);
                cmoon::test::assert_equal(l2::size(), 1);
                cmoon::test::assert_equal(l3::size(), 4);
            }
    };

    export
    class value_list_get_test : public cmoon::test::test_case
    {
        public:
            value_list_get_test()
                : cmoon::test::test_case{"value_list_get_test"} {}

            void operator()() final
            {
                using l = cmoon::meta::value_list<5, 'c', 4.2, 0>;

                cmoon::test::assert_equal(l::get<0>(), 5);
                cmoon::test::assert_equal(l::get<1>(), 'c');
                cmoon::test::assert_equal(l::get<2>(), 4.2);
                cmoon::test::assert_equal(l::get<3>(), 0);
            }
    };

    export
    class value_list_contains_test : public cmoon::test::test_case
    {
        public:
            value_list_contains_test()
                : cmoon::test::test_case{"value_list_contains_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<5, 'c', 4.2, 0>;
                using l2 = cmoon::meta::value_list<>;

                cmoon::test::assert_true(l1::contains(5));
                cmoon::test::assert_true(l1::contains('c'));
                cmoon::test::assert_true(l1::contains(4.2));
                cmoon::test::assert_true(l1::contains(0));

                cmoon::test::assert_false(l1::contains(4.3));
                cmoon::test::assert_false(l1::contains("hello"));
                cmoon::test::assert_false(l1::contains(35));

                cmoon::test::assert_false(l2::contains(5));
                cmoon::test::assert_false(l2::contains('c'));
                cmoon::test::assert_false(l2::contains(4.2));
                cmoon::test::assert_false(l2::contains(0));
                cmoon::test::assert_false(l1::contains(4.3));
                cmoon::test::assert_false(l1::contains("hello"));
                cmoon::test::assert_false(l1::contains(35));
            }
    };

    export
    class value_list_tuple_test : public cmoon::test::test_case
    {
        public:
            value_list_tuple_test()
                : cmoon::test::test_case{"value_list_tuple_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<5, 'c', 4.2, 0>;
                using l2 = cmoon::meta::value_list<>;

                cmoon::test::assert_equal(l1::to_tuple(), std::tuple{5, 'c', 4.2, 0});
                cmoon::test::assert_equal(l2::to_tuple(), std::tuple{});
            }
    };

    export
    class value_list_all_of_test : public cmoon::test::test_case
    {
        public:
            value_list_all_of_test()
                : cmoon::test::test_case{"value_list_all_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<5, 'c', 4.2, 0>;
                using l2 = cmoon::meta::value_list<>;

                cmoon::test::assert_true(l1::all_of([] (const auto& v) { return v < 100; }));
                cmoon::test::assert_true(l2::all_of([] (const auto& v) { return v < 100; }));
            }
    };

    export
    class value_list_any_of_test : public cmoon::test::test_case
    {
        public:
            value_list_any_of_test()
                : cmoon::test::test_case{"value_list_any_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<5, 'c', 4.2, 0>;
                using l2 = cmoon::meta::value_list<>;

                cmoon::test::assert_true(l1::any_of([] (const auto& v) { return v > 4; }));
                cmoon::test::assert_false(l2::any_of([] (const auto& v) { return v > 4; }));
            }
    };

    export
    class value_list_none_of_test : public cmoon::test::test_case
    {
        public:
            value_list_none_of_test()
                : cmoon::test::test_case{"value_list_none_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<5, 'c', 4.2, 0>;
                using l2 = cmoon::meta::value_list<>;

                cmoon::test::assert_true(l1::none_of([] (const auto& v) { return v == 'g'; }));
                cmoon::test::assert_true(l2::none_of([] (const auto& v) { return v == 'g'; }));
            }
    };

    export
    class value_list_for_each_test : public cmoon::test::test_case
    {
        public:
            value_list_for_each_test()
                : cmoon::test::test_case{"value_list_for_each_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4>;
                using l2 = cmoon::meta::value_list<>;

                int c1 {0};

                l1::for_each([&] (const auto& v) { c1 += v; });
                cmoon::test::assert_equal(c1, 10);

                int c2 {0};
                l2::for_each([&] (const auto& v) { c2 += v; });
                cmoon::test::assert_equal(c2, 0);
            }
    };

    export
    class value_list_append_test : public cmoon::test::test_case
    {
        public:
            value_list_append_test()
                : cmoon::test::test_case{"value_list_append_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4>;

                using l2 = l1::append<5, 6, 7, 8>;

                cmoon::test::assert_equal(l2::size(), 8);
                cmoon::test::assert_equal(l2::get<0>(), 1);
                cmoon::test::assert_equal(l2::get<1>(), 2);
                cmoon::test::assert_equal(l2::get<2>(), 3);
                cmoon::test::assert_equal(l2::get<3>(), 4);
                cmoon::test::assert_equal(l2::get<4>(), 5);
                cmoon::test::assert_equal(l2::get<5>(), 6);
                cmoon::test::assert_equal(l2::get<6>(), 7);
                cmoon::test::assert_equal(l2::get<7>(), 8);
            }
    };

    export
    class value_list_concatenate_test : public cmoon::test::test_case
    {
        public:
            value_list_concatenate_test()
                : cmoon::test::test_case{"value_list_concatenate_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4>;
                using l2 = cmoon::meta::value_list<5, 6, 7, 8>;
                using l3 = cmoon::meta::value_list<>;
                using l4 = cmoon::meta::value_list<9, 10>;

                using l5 = l1::concatenate<l2, l3, l4>;

                cmoon::test::assert_equal(l5::size(), 10);
                cmoon::test::assert_equal(l5::get<0>(), 1);
                cmoon::test::assert_equal(l5::get<1>(), 2);
                cmoon::test::assert_equal(l5::get<2>(), 3);
                cmoon::test::assert_equal(l5::get<3>(), 4);
                cmoon::test::assert_equal(l5::get<4>(), 5);
                cmoon::test::assert_equal(l5::get<5>(), 6);
                cmoon::test::assert_equal(l5::get<6>(), 7);
                cmoon::test::assert_equal(l5::get<7>(), 8);
                cmoon::test::assert_equal(l5::get<8>(), 9);
                cmoon::test::assert_equal(l5::get<9>(), 10);
            }
    };

    export
    class value_list_filter_test : public cmoon::test::test_case
    {
        template<auto V>
        struct filter_func : std::bool_constant<V <= 5> {};

        public:
            value_list_filter_test()
                : cmoon::test::test_case{"value_list_filter_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;

                using l2 = l1::filter<filter_func>;

                cmoon::test::assert_equal(l2::size(), 5);
                cmoon::test::assert_equal(l2::get<0>(), 1);
                cmoon::test::assert_equal(l2::get<1>(), 2);
                cmoon::test::assert_equal(l2::get<2>(), 3);
                cmoon::test::assert_equal(l2::get<3>(), 4);
                cmoon::test::assert_equal(l2::get<4>(), 5);
            }
    };

    export
    class value_list_transform_test : public cmoon::test::test_case
    {
        template<auto V>
        struct transform_func
        {
            static constexpr auto value {V * V};
        };

        public:
            value_list_transform_test()
                : cmoon::test::test_case{"value_list_transform_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;

                using l2 = l1::transform<transform_func>;

                cmoon::test::assert_equal(l2::size(), 10);
                cmoon::test::assert_equal(l2::get<0>(), 1);
                cmoon::test::assert_equal(l2::get<1>(), 4);
                cmoon::test::assert_equal(l2::get<2>(), 9);
                cmoon::test::assert_equal(l2::get<3>(), 16);
                cmoon::test::assert_equal(l2::get<4>(), 25);
                cmoon::test::assert_equal(l2::get<5>(), 36);
                cmoon::test::assert_equal(l2::get<6>(), 49);
                cmoon::test::assert_equal(l2::get<7>(), 64);
                cmoon::test::assert_equal(l2::get<8>(), 81);
                cmoon::test::assert_equal(l2::get<9>(), 100);
            }
    };

    export
    class value_list_transform_to_types_test : public cmoon::test::test_case
    {
        template<auto V>
        struct transform_func : std::type_identity<std::integral_constant<decltype(V), V>> {};

        public:
            value_list_transform_to_types_test()
                : cmoon::test::test_case{"value_list_transform_to_types_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;

                using l2 = l1::transform_to_types<transform_func>;

                cmoon::test::assert_equal(l2::size(), 10);
                cmoon::test::assert_equal(l2::type<0>{}(), 1);
                cmoon::test::assert_equal(l2::type<1>{}(), 2);
                cmoon::test::assert_equal(l2::type<2>{}(), 3);
                cmoon::test::assert_equal(l2::type<3>{}(), 4);
                cmoon::test::assert_equal(l2::type<4>{}(), 5);
                cmoon::test::assert_equal(l2::type<5>{}(), 6);
                cmoon::test::assert_equal(l2::type<6>{}(), 7);
                cmoon::test::assert_equal(l2::type<7>{}(), 8);
                cmoon::test::assert_equal(l2::type<8>{}(), 9);
                cmoon::test::assert_equal(l2::type<9>{}(), 10);
            }
    };

    export
    class value_list_sub_list_test : public cmoon::test::test_case
    {
        public:
            value_list_sub_list_test()
                : cmoon::test::test_case{"value_list_sub_list_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;

                using l2 = l1::sub_list<0>;
                using l3 = l1::sub_list<2>;
                using l4 = l1::sub_list<0, 3>;
                using l5 = l1::sub_list<9>;
                using l6 = l1::sub_list<8, 4>;

                cmoon::test::assert_equal(l2::size(), 10);
                cmoon::test::assert_equal(l3::size(), 8);
                cmoon::test::assert_equal(l4::size(), 3);
                cmoon::test::assert_equal(l5::size(), 1);
                cmoon::test::assert_equal(l6::size(), 2);

                cmoon::test::assert_equal(l2::get<0>(), 1);
                cmoon::test::assert_equal(l2::get<1>(), 2);
                cmoon::test::assert_equal(l2::get<2>(), 3);
                cmoon::test::assert_equal(l2::get<3>(), 4);
                cmoon::test::assert_equal(l2::get<4>(), 5);
                cmoon::test::assert_equal(l2::get<5>(), 6);
                cmoon::test::assert_equal(l2::get<6>(), 7);
                cmoon::test::assert_equal(l2::get<7>(), 8);
                cmoon::test::assert_equal(l2::get<8>(), 9);
                cmoon::test::assert_equal(l2::get<9>(), 10);

                cmoon::test::assert_equal(l3::get<0>(), 3);
                cmoon::test::assert_equal(l3::get<1>(), 4);
                cmoon::test::assert_equal(l3::get<2>(), 5);
                cmoon::test::assert_equal(l3::get<3>(), 6);
                cmoon::test::assert_equal(l3::get<4>(), 7);
                cmoon::test::assert_equal(l3::get<5>(), 8);
                cmoon::test::assert_equal(l3::get<6>(), 9);
                cmoon::test::assert_equal(l3::get<7>(), 10);

                cmoon::test::assert_equal(l4::get<0>(), 1);
                cmoon::test::assert_equal(l4::get<1>(), 2);
                cmoon::test::assert_equal(l4::get<2>(), 3);

                cmoon::test::assert_equal(l5::get<0>(), 10);

                cmoon::test::assert_equal(l6::get<0>(), 9);
                cmoon::test::assert_equal(l6::get<1>(), 10);
            }
    };

    export
    class transform_values_test : public cmoon::test::test_case
    {
        template<auto V>
        struct transform_func
        {
            static constexpr auto value {V * V};
        };

        public:
            transform_values_test()
                : cmoon::test::test_case{"transform_values_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::transform_values<transform_func,
                    1,
                    2,
                    3,
                    4,
                    5
                >;

                cmoon::test::assert_equal(l1::size(), 5);
                cmoon::test::assert_equal(l1::get<0>(), 1);
                cmoon::test::assert_equal(l1::get<1>(), 4);
                cmoon::test::assert_equal(l1::get<2>(), 9);
                cmoon::test::assert_equal(l1::get<3>(), 16);
                cmoon::test::assert_equal(l1::get<4>(), 25);
            }
    };

    export
    class filter_values_test : public cmoon::test::test_case
    {
        template<auto V>
        struct filter_func : std::bool_constant<V % 2 == 0> {};

        public:
            filter_values_test()
                : cmoon::test::test_case{"filter_values_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::filter_values<filter_func,
                    1,
                    2,
                    3,
                    4,
                    5
                >;

                cmoon::test::assert_equal(l1::size(), 2);
                cmoon::test::assert_equal(l1::get<0>(), 2);
                cmoon::test::assert_equal(l1::get<1>(), 4);
            }
    };

    export
    class concatenate_values_test : public cmoon::test::test_case
    {
        public:
            concatenate_values_test()
                : cmoon::test::test_case{"concatenate_values_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::value_list<1, 2>;
                using l2 = cmoon::meta::value_list<3, 4>;
                using l3 = cmoon::meta::value_list<>;
                using l4 = cmoon::meta::value_list<5, 6>;

                using l5 = cmoon::meta::concatenate_values<l1, l2, l3, l4>;
                using l6 = cmoon::meta::concatenate_values<l1, l1>;
                using l7 = cmoon::meta::concatenate_values<l3, l3, l3>;

                cmoon::test::assert_equal(l5::size(), 6);
                cmoon::test::assert_equal(l5::get<0>(), 1);
                cmoon::test::assert_equal(l5::get<1>(), 2);
                cmoon::test::assert_equal(l5::get<2>(), 3);
                cmoon::test::assert_equal(l5::get<3>(), 4);
                cmoon::test::assert_equal(l5::get<4>(), 5);
                cmoon::test::assert_equal(l5::get<5>(), 6);

                cmoon::test::assert_equal(l6::size(), 4);
                cmoon::test::assert_equal(l6::get<0>(), 1);
                cmoon::test::assert_equal(l6::get<1>(), 2);
                cmoon::test::assert_equal(l6::get<2>(), 1);
                cmoon::test::assert_equal(l6::get<3>(), 2);

                cmoon::test::assert_equal(l7::size(), 0);
            }
    };

    export
    class iota_test : public cmoon::test::test_case
    {
        public:
            iota_test()
                : cmoon::test::test_case{"iota_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::iota<0, 10>;
                using l2 = cmoon::meta::iota<0, 0>;
                using l3 = cmoon::meta::iota<10, 4>;
                using l4 = cmoon::meta::iota<-2, 8>;

                cmoon::test::assert_equal(l1::size(), 10);
                cmoon::test::assert_equal(l1::get<0>(), 0);
                cmoon::test::assert_equal(l1::get<1>(), 1);
                cmoon::test::assert_equal(l1::get<2>(), 2);
                cmoon::test::assert_equal(l1::get<3>(), 3);
                cmoon::test::assert_equal(l1::get<4>(), 4);
                cmoon::test::assert_equal(l1::get<5>(), 5);
                cmoon::test::assert_equal(l1::get<6>(), 6);
                cmoon::test::assert_equal(l1::get<7>(), 7);
                cmoon::test::assert_equal(l1::get<8>(), 8);
                cmoon::test::assert_equal(l1::get<9>(), 9);

                cmoon::test::assert_equal(l2::size(), 0);

                cmoon::test::assert_equal(l3::size(), 6);
                cmoon::test::assert_equal(l3::get<0>(), 10);
                cmoon::test::assert_equal(l3::get<1>(), 9);
                cmoon::test::assert_equal(l3::get<2>(), 8);
                cmoon::test::assert_equal(l3::get<3>(), 7);
                cmoon::test::assert_equal(l3::get<4>(), 6);
                cmoon::test::assert_equal(l3::get<5>(), 5);

                cmoon::test::assert_equal(l4::size(), 10);
                cmoon::test::assert_equal(l4::get<0>(), -2);
                cmoon::test::assert_equal(l4::get<1>(), -1);
                cmoon::test::assert_equal(l4::get<2>(), 0);
                cmoon::test::assert_equal(l4::get<3>(), 1);
                cmoon::test::assert_equal(l4::get<4>(), 2);
                cmoon::test::assert_equal(l4::get<5>(), 3);
                cmoon::test::assert_equal(l4::get<6>(), 4);
                cmoon::test::assert_equal(l4::get<7>(), 5);
                cmoon::test::assert_equal(l4::get<8>(), 6);
                cmoon::test::assert_equal(l4::get<9>(), 7);
            }
    };

    export
    class index_sequence_test : public cmoon::test::test_case
    {
        public:
            index_sequence_test()
                : cmoon::test::test_case{"index_sequence_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::index_sequence<1, 2, 3>;

                cmoon::test::assert_equal(l1::size(), 3);
                cmoon::test::assert_equal(l1::get<0>(), 1);
                cmoon::test::assert_equal(l1::get<1>(), 2);
                cmoon::test::assert_equal(l1::get<2>(), 3);
            }
    };

    export
    class make_integer_sequence_test : public cmoon::test::test_case
    {
        public:
            make_integer_sequence_test()
                : cmoon::test::test_case{"make_integer_sequence_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::make_integer_sequence<std::size_t, 8>;

                cmoon::test::assert_equal(l1::size(), 8);
                cmoon::test::assert_equal(l1::get<0>(), 0);
                cmoon::test::assert_equal(l1::get<1>(), 1);
                cmoon::test::assert_equal(l1::get<2>(), 2);
                cmoon::test::assert_equal(l1::get<3>(), 3);
                cmoon::test::assert_equal(l1::get<4>(), 4);
                cmoon::test::assert_equal(l1::get<5>(), 5);
                cmoon::test::assert_equal(l1::get<6>(), 6);
                cmoon::test::assert_equal(l1::get<7>(), 7);
            }
    };

    export
    class make_index_sequence_test : public cmoon::test::test_case
    {
        public:
            make_index_sequence_test()
                : cmoon::test::test_case{"make_index_sequence_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::make_index_sequence<8>;

                cmoon::test::assert_equal(l1::size(), 8);
                cmoon::test::assert_equal(l1::get<0>(), 0);
                cmoon::test::assert_equal(l1::get<1>(), 1);
                cmoon::test::assert_equal(l1::get<2>(), 2);
                cmoon::test::assert_equal(l1::get<3>(), 3);
                cmoon::test::assert_equal(l1::get<4>(), 4);
                cmoon::test::assert_equal(l1::get<5>(), 5);
                cmoon::test::assert_equal(l1::get<6>(), 6);
                cmoon::test::assert_equal(l1::get<7>(), 7);
            }
    };

    export
    class index_sequence_for_test : public cmoon::test::test_case
    {
        public:
            index_sequence_for_test()
                : cmoon::test::test_case{"index_sequence_for_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::index_sequence_for<int, double, float, int>;

                cmoon::test::assert_equal(l1::size(), 4);
                cmoon::test::assert_equal(l1::get<0>(), 0);
                cmoon::test::assert_equal(l1::get<1>(), 1);
                cmoon::test::assert_equal(l1::get<2>(), 2);
                cmoon::test::assert_equal(l1::get<3>(), 3);
            }
    };

    export
    class gen_value_list_test : public cmoon::test::test_case
    {
        public:
            gen_value_list_test()
                : cmoon::test::test_case{"gen_value_list_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::gen_value_list_t<5, 4.2>;

                cmoon::test::assert_equal(l1::size(), 5);
                cmoon::test::assert_equal(l1::get<0>(), 4.2);
                cmoon::test::assert_equal(l1::get<1>(), 4.2);
                cmoon::test::assert_equal(l1::get<2>(), 4.2);
                cmoon::test::assert_equal(l1::get<3>(), 4.2);
                cmoon::test::assert_equal(l1::get<4>(), 4.2);
            }
    };
}