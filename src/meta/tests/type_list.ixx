export module cmoon.tests.meta.type_list;

import std.core;

import cmoon.test;
import cmoon.meta;

namespace cmoon::tests::meta
{
    export
    class type_list_size_test : public cmoon::test::test_case
    {
        public:
            type_list_size_test()
                : cmoon::test::test_case{"type_list_size_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                cmoon::test::assert_equal(l1::size(), 0);
                cmoon::test::assert_equal(l2::size(), 1);
                cmoon::test::assert_equal(l3::size(), 4);
            }
    };

    export
    class type_list_empty_test : public cmoon::test::test_case
    {
        public:
            type_list_empty_test()
                : cmoon::test::test_case{"type_list_empty_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                cmoon::test::assert_true(l1::empty());
                cmoon::test::assert_false(l2::empty());
                cmoon::test::assert_false(l3::empty());
            }
    };

    export
    class type_list_type_test : public cmoon::test::test_case
    {
        public:
            type_list_type_test()
                : cmoon::test::test_case{"type_list_type_test"} {}

            void operator()() final
            {
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                cmoon::test::assert_is_type<l2::type<0>, int>();

                cmoon::test::assert_is_type<l3::type<0>, double>();
                cmoon::test::assert_is_type<l3::type<1>, float>();
                cmoon::test::assert_is_type<l3::type<2>, int>();
                cmoon::test::assert_is_type<l3::type<3>, char>();
            }
    };

    export
    class type_list_index_test : public cmoon::test::test_case
    {
        public:
            type_list_index_test()
                : cmoon::test::test_case{"type_list_index_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                
                cmoon::test::assert_equal(l1::index<int>(), l1::npos);

                cmoon::test::assert_equal(l2::index<int>(), 0);
                cmoon::test::assert_equal(l2::index<float>(), l2::npos);

                cmoon::test::assert_equal(l3::index<double>(), 0);
                cmoon::test::assert_equal(l3::index<float>(), 1);
                cmoon::test::assert_equal(l3::index<int>(), 2);
                cmoon::test::assert_equal(l3::index<char>(), 3);
                cmoon::test::assert_equal(l3::index<void*>(), l3::npos);
            }
    };

    export
    class type_list_contains_test : public cmoon::test::test_case
    {
        public:
            type_list_contains_test()
                : cmoon::test::test_case{"type_list_contains_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                
                cmoon::test::assert_false(l1::contains<int>());

                cmoon::test::assert_true(l2::contains<int>());
                cmoon::test::assert_false(l2::contains<float>());

                cmoon::test::assert_true(l3::contains<double>());
                cmoon::test::assert_true(l3::contains<float>());
                cmoon::test::assert_true(l3::contains<int>());
                cmoon::test::assert_true(l3::contains<char>());
                cmoon::test::assert_false(l3::contains<void*>());
            }
    };

    export
    class type_list_all_of_test : public cmoon::test::test_case
    {
        public:
            type_list_all_of_test()
                : cmoon::test::test_case{"type_list_all_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                
                cmoon::test::assert_true(l1::all_of<std::is_integral>());

                cmoon::test::assert_true(l2::all_of<std::is_integral>());
                cmoon::test::assert_false(l2::all_of<std::is_floating_point>());

                cmoon::test::assert_true(l3::all_of<std::is_object>());
                cmoon::test::assert_false(l3::all_of<std::is_integral>());
                cmoon::test::assert_false(l3::all_of<std::is_floating_point>());

                cmoon::test::assert_true(l4::all_of<std::is_trivial>());
                cmoon::test::assert_false(l4::all_of<std::is_arithmetic>());
            }
    };

    export
    class type_list_any_of_test : public cmoon::test::test_case
    {
        public:
            type_list_any_of_test()
                : cmoon::test::test_case{"type_list_any_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_false(l1::any_of<std::is_integral>());

                cmoon::test::assert_true(l2::any_of<std::is_integral>());
                cmoon::test::assert_false(l2::any_of<std::is_floating_point>());
                cmoon::test::assert_false(l2::any_of<std::is_abstract>());

                cmoon::test::assert_true(l3::any_of<std::is_object>());

                cmoon::test::assert_true(l4::any_of<std::is_trivial>());
                cmoon::test::assert_true(l4::any_of<std::is_pointer>());
            }
    };

    export
    class type_list_none_of_test : public cmoon::test::test_case
    {
        public:
            type_list_none_of_test()
                : cmoon::test::test_case{"type_list_none_of_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_true(l1::none_of<std::is_integral>());

                cmoon::test::assert_false(l2::none_of<std::is_integral>());
                cmoon::test::assert_true(l2::none_of<std::is_floating_point>());
                cmoon::test::assert_true(l2::none_of<std::is_abstract>());

                cmoon::test::assert_false(l3::none_of<std::is_object>());

                cmoon::test::assert_false(l4::none_of<std::is_trivial>());
                cmoon::test::assert_false(l4::none_of<std::is_pointer>());
            }
    };

    export
    class type_list_for_each_test : public cmoon::test::test_case
    {
        static std::size_t count_integral;

        template<class T>
        struct count_integral_t
        {
            constexpr void operator()()
            {
                count_integral += std::is_integral_v<T>;
            }
        };

        static std::size_t count_pointer;

        template<class T>
        struct count_pointer_t
        {
            constexpr void operator()()
            {
                count_pointer += std::is_pointer_v<T>;
            }
        };

        public:
            type_list_for_each_test()
                : cmoon::test::test_case{"type_list_for_each_test"} {}

            void set_up() final
            {
                count_integral = 0;
                count_pointer  = 0;
            }

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                l1::for_each<count_integral_t>();
                l1::for_each<count_pointer_t>();

                cmoon::test::assert_equal(count_integral, 0);
                cmoon::test::assert_equal(count_pointer, 0);

                l2::for_each<count_integral_t>();
                l2::for_each<count_pointer_t>();

                cmoon::test::assert_equal(count_integral, 1);
                cmoon::test::assert_equal(count_pointer, 0);

                l3::for_each<count_integral_t>();
                l3::for_each<count_pointer_t>();

                cmoon::test::assert_equal(count_integral, 3);
                cmoon::test::assert_equal(count_pointer, 0);

                l4::for_each<count_integral_t>();
                l4::for_each<count_pointer_t>();

                cmoon::test::assert_equal(count_integral, 5);
                cmoon::test::assert_equal(count_pointer, 1);
            }
    };

    std::size_t type_list_for_each_test::count_integral;
    std::size_t type_list_for_each_test::count_pointer;

    export
    class type_list_append_test : public cmoon::test::test_case
    {
        public:
            type_list_append_test()
                : cmoon::test::test_case{"type_list_append_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_is_type<l1::append<>, l1>();
                cmoon::test::assert_is_type<l1::append<int>, l2>();
                cmoon::test::assert_is_type<l1::append<double, float, int, char>, l3>();
                cmoon::test::assert_is_type<l1::append<double, float, int, char, void*>, l4>();

                cmoon::test::assert_is_type<l2::append<int>, cmoon::meta::type_list<int, int>>();
                cmoon::test::assert_is_type<l2::append<double>, cmoon::meta::type_list<int, double>>();
            }
    };

    export
    class type_list_concatenate_test : public cmoon::test::test_case
    {
        public:
            type_list_concatenate_test()
                : cmoon::test::test_case{"type_list_concatenate_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_is_type<l1::concatenate<>, l1>();
                cmoon::test::assert_is_type<l1::concatenate<cmoon::meta::type_list<>>, l1>();
                cmoon::test::assert_is_type<l1::concatenate<l2>, l2>();
                cmoon::test::assert_is_type<l1::concatenate<l3>, l3>();
                cmoon::test::assert_is_type<l1::concatenate<l4>, l4>();

                cmoon::test::assert_is_type<l2::concatenate<>, l2>();
                cmoon::test::assert_is_type<l2::concatenate<cmoon::meta::type_list<>>, l2>();
                cmoon::test::assert_is_type<l2::concatenate<l2>, cmoon::meta::type_list<int, int>>();
                cmoon::test::assert_is_type<l2::concatenate<l3>, cmoon::meta::type_list<int, double, float, int, char>>();
            }
    };

    export
    class type_list_filter_test : public cmoon::test::test_case
    {
        public:
            type_list_filter_test()
                : cmoon::test::test_case{"type_list_filter_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_is_type<l1::filter<std::is_integral>, l1>();

                cmoon::test::assert_is_type<l2::filter<std::is_integral>, l2>();
                cmoon::test::assert_is_type<l2::filter<std::is_floating_point>, l1>();

                cmoon::test::assert_is_type<l3::filter<std::is_integral>, cmoon::meta::type_list<int, char>>();
                cmoon::test::assert_is_type<l3::filter<std::is_floating_point>, cmoon::meta::type_list<double, float>>();

                cmoon::test::assert_is_type<l4::filter<std::is_pointer>, cmoon::meta::type_list<void*>>();
                cmoon::test::assert_is_type<l4::filter<std::is_abstract>, l1>();
            }
    };

    export
    class type_list_transform_test : public cmoon::test::test_case
    {
        template<class T>
        struct flip_integral_floating : std::conditional<std::integral<T>,
                                                         float,
                                                         std::conditional_t<std::floating_point<T>,
                                                            int,
                                                            T>> {};

        public:
            type_list_transform_test()
                : cmoon::test::test_case{"type_list_transform_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_is_type<l1::transform<flip_integral_floating>, l1>();

                cmoon::test::assert_is_type<l2::transform<flip_integral_floating>, cmoon::meta::type_list<float>>();

                cmoon::test::assert_is_type<l3::transform<flip_integral_floating>, cmoon::meta::type_list<int, int, float, float>>();

                cmoon::test::assert_is_type<l4::transform<flip_integral_floating>, cmoon::meta::type_list<int, int, float, float, void*>>();
            }
    };

    export
    class type_list_sub_list_test : public cmoon::test::test_case
    {
        public:
            type_list_sub_list_test()
                : cmoon::test::test_case{"type_list_sub_list_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;

                cmoon::test::assert_is_type<l1::sub_list<0>, l1>();
                cmoon::test::assert_is_type<l2::sub_list<0>, l2>();
                cmoon::test::assert_is_type<l3::sub_list<0>, l3>();

                cmoon::test::assert_is_type<l2::sub_list<1>, l1>();
                cmoon::test::assert_is_type<l3::sub_list<1>, cmoon::meta::type_list<float, int, char>>();

                cmoon::test::assert_is_type<l3::sub_list<2>, cmoon::meta::type_list<int, char>>();
                cmoon::test::assert_is_type<l3::sub_list<3>, cmoon::meta::type_list<char>>();
                cmoon::test::assert_is_type<l3::sub_list<4>, cmoon::meta::type_list<>>();

                cmoon::test::assert_is_type<l3::sub_list<0, 0>, cmoon::meta::type_list<>>();
                cmoon::test::assert_is_type<l3::sub_list<0, 1>, cmoon::meta::type_list<double>>();
                cmoon::test::assert_is_type<l3::sub_list<0, 2>, cmoon::meta::type_list<double, float>>();
                cmoon::test::assert_is_type<l3::sub_list<0, 3>, cmoon::meta::type_list<double, float, int>>();
                cmoon::test::assert_is_type<l3::sub_list<0, 4>, l3>();
                cmoon::test::assert_is_type<l3::sub_list<0, 5>, l3>();

                cmoon::test::assert_is_type<l3::sub_list<1, 2>, cmoon::meta::type_list<float, int>>();
                cmoon::test::assert_is_type<l3::sub_list<1, 0>, l1>();
            }
    };

    export
    class type_list_unique_test : public cmoon::test::test_case
    {
        public:
            type_list_unique_test()
                : cmoon::test::test_case{"type_list_unique_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, int, float>;

                cmoon::test::assert_is_type<l1::unique, l1>();
                cmoon::test::assert_is_type<l2::unique, l2>();
                cmoon::test::assert_is_type<l3::unique, l3>();
                cmoon::test::assert_is_type<l4::unique, l3>();

                cmoon::test::assert_true(l1::is_unique());
                cmoon::test::assert_true(l2::is_unique());
                cmoon::test::assert_true(l3::is_unique());
                cmoon::test::assert_false(l4::is_unique());

                cmoon::test::assert_true(l1::is_all_same_type());
                cmoon::test::assert_true(l2::is_all_same_type());
                cmoon::test::assert_false(l3::is_all_same_type());
                cmoon::test::assert_false(l4::is_all_same_type());
            }
    };

    export
    class type_list_find_test : public cmoon::test::test_case
    {
        public:
            type_list_find_test()
                : cmoon::test::test_case{"type_list_find_test"} {}

            void operator()() final
            {
                using l1 = cmoon::meta::type_list<>;
                using l2 = cmoon::meta::type_list<int>;
                using l3 = cmoon::meta::type_list<double, float, int, char>;
                using l4 = cmoon::meta::type_list<double, float, int, char, void*>;

                cmoon::test::assert_is_type<l1::find<std::is_integral>, cmoon::nonesuch>();
                cmoon::test::assert_is_type<l2::find<std::is_integral>, int>();
                cmoon::test::assert_is_type<l3::find<std::is_floating_point>, double>();
                cmoon::test::assert_is_type<l4::find<std::is_pointer>, void*>();
                cmoon::test::assert_is_type<l4::find<std::is_abstract>, cmoon::nonesuch>();
            }
    };
}