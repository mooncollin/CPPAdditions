export module cmoon.tests.fixed_valarray;

import std.core;

import cmoon.test;
import cmoon.fixed_valarray;

namespace cmoon::tests::fixed_valarray
{
    export
    cmoon::test::test_suite get_tests()
    {
        cmoon::test::test_suite suite{"fixed_valarray library tests"};

        return std::move(suite);
    }
}