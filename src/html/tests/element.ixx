export module cmoon.tests.html.element;

import std.core;

import cmoon.test;
import cmoon.html;

namespace cmoon::tests::html
{
    export
    class element_constructor_test : public cmoon::test::test_case
    {

        public:
            element_constructor_test()
                : cmoon::test::test_case{"element_constructor_test"} {}

            void operator()() final
            {
                auto e = cmoon::html::a_tag();

                cmoon::html::element e2 {cmoon::html::a_tag, cmoon::html::static_attributes{
                    cmoon::html::attributes::async{}
                }};

                auto e3 = cmoon::html::a_tag(cmoon::html::static_attributes{
                    cmoon::html::attributes::async{}
                }, e2);

                cmoon::html::element e4 {cmoon::html::a_tag, cmoon::html::no_attributes, "Hello!"};

                auto e5 = cmoon::html::a_tag(std::cref(e2.attributes()), std::ref(e), std::cref(e3), "Hello!");
            }
    };

    export
    class element_print_test : public cmoon::test::test_case
    {
        public:
            element_print_test()
                : cmoon::test::test_case{"element_print_test"} {}

            void operator()() final
            {
                auto e = cmoon::html::a_tag();

                constexpr cmoon::html::element e2 {cmoon::html::a_tag, cmoon::html::static_attributes{
                    cmoon::html::attributes::async{}
                }};

                auto e3 = cmoon::html::a_tag(cmoon::html::make_attributes(
                    cmoon::html::attributes::async{},
                    cmoon::html::attributes::accesskey{'H'}
                ), e);

                auto e4 = cmoon::html::a_tag({}, e, "some text", e2);

                std::stringstream ss;

                ss << e;
                cmoon::test::assert_equal(ss.str(), "<a></a>");

                ss.str("");
                ss << e2;
                cmoon::test::assert_equal(ss.str(), "<a async></a>");

                ss.str("");
                ss << e3;
                cmoon::test::assert_equal(ss.str(), "<a async accesskey=\"H\"><a></a></a>");

                ss.str("");
                ss << e4;
                cmoon::test::assert_equal(ss.str(), "<a><a></a>some text<a async></a></a>");
                std::cout << sizeof(e) << '\n';
                std::cout << sizeof(e2) << '\n';
                std::cout << sizeof(e3) << '\n';
                std::cout << sizeof(e4) << '\n';
            }
    };
}