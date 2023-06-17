export module cmoon.tests.html:attributes;

import std.core;

import cmoon.test;
import cmoon.html;

namespace cmoon::tests::html
{
    export
    class attributes_accesskey_test : public cmoon::test::test_case
    {
        public:
            attributes_accesskey_test()
                : cmoon::test::test_case{"attributes_accesskey_test"} {}

            void operator()() final
            {
                constexpr cmoon::html::attributes::accesskey a1 {'C'};
                constexpr cmoon::html::attributes::accesskey::constant<'H'> a2;

                cmoon::test::assert_equal(a1.value, 'C');
                
                // MSVC crashes on this test
                // cmoon::test::assert_equal(a2.value, 'H');

                std::stringstream ss;
                ss << a1;
                cmoon::test::assert_equal(ss.str(), "accesskey=\"C\"");

                ss.str("");

                ss << a2;
                cmoon::test::assert_equal(ss.str(), "accesskey=\"H\"");
            }
    };

    export
    class attributes_async_test : public cmoon::test::test_case
    {
        public:
            attributes_async_test()
                : cmoon::test::test_case{"attributes_async_test"} {}

            void operator()() final
            {
                constexpr cmoon::html::attributes::async a1;

                std::stringstream ss;
                ss << a1;
                cmoon::test::assert_equal(ss.str(), "async");
            }
    };
}