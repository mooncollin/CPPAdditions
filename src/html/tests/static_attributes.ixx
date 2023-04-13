export module cmoon.tests.html.static_attributes;

import std.core;

import cmoon.test;
import cmoon.html;

namespace cmoon::tests::html
{
    export
    class static_attributes_constructor_test : public cmoon::test::test_case
    {
        public:
            static_attributes_constructor_test()
                : cmoon::test::test_case{"static_attributes_constructor_test"} {}

            void operator()() final
            {
                constexpr cmoon::html::static_attributes a1 {
                    cmoon::html::attributes::accesskey{'C'}
                };

                constexpr cmoon::html::static_attributes a2 {
                    cmoon::html::attributes::accesskey::constant<'H'>{}
                };

                constexpr cmoon::html::static_attributes a3 {
                    cmoon::html::attributes::accesskey{'C'},
                    cmoon::html::attributes::async{}
                };

                using a4_t = cmoon::html::static_attributes<
                    cmoon::html::attributes::async,
                    cmoon::html::attributes::accesskey
                >;

                constexpr a4_t a4 {
                    cmoon::html::attributes::accesskey{'H'},
                    cmoon::html::attributes::async{}
                };
            }
    };

    export
    class static_attributes_get_test : public cmoon::test::test_case
    {
        public:
            static_attributes_get_test()
                : cmoon::test::test_case{"static_attributes_get_test"} {}

            void operator()() final
            {
                constexpr cmoon::html::static_attributes a1 {
                    cmoon::html::attributes::accesskey{'C'},
                    cmoon::html::attributes::async{}
                };

                constexpr cmoon::html::static_attributes a2 {
                    cmoon::html::attributes::accesskey::constant<'H'>{}
                };

                {
                    constexpr auto v {a1.get<cmoon::html::attributes::accesskey>()};
                    cmoon::test::assert_is_type<std::decay_t<decltype(v)>, cmoon::html::attributes::accesskey>();
                }

                {
                    constexpr auto v {a1.get<cmoon::html::attributes::async>()};
                    cmoon::test::assert_is_type<std::decay_t<decltype(v)>, cmoon::html::attributes::async>();
                }

                {
                    constexpr auto v {a2.get<cmoon::html::attributes::accesskey>()};
                    cmoon::test::assert_is_type<std::decay_t<decltype(v)>, cmoon::html::attributes::accesskey::constant<'H'>>();
                }
            }
    };

    export
    class static_attributes_print_test : public cmoon::test::test_case
    {
        public:
            static_attributes_print_test()
                : cmoon::test::test_case{"static_attributes_print_test"} {}

            void operator()() final
            {
                constexpr cmoon::html::static_attributes a1 {
                    cmoon::html::attributes::accesskey{'C'},
                    cmoon::html::attributes::async{}
                };

                constexpr cmoon::html::static_attributes a2 {
                    cmoon::html::attributes::accesskey::constant<'H'>{}
                };

                std::stringstream ss;

                ss << a1;
                cmoon::test::assert_equal(ss.str(), "accesskey=\"C\" async");

                ss.str("");

                ss << a2;
                cmoon::test::assert_equal(ss.str(), "accesskey=\"H\"");
            }
    };
}