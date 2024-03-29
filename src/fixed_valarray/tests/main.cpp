import std.core;

import cmoon.test;

import cmoon.tests.fixed_valarray;

int main()
{
	auto suite {cmoon::tests::fixed_valarray::get_tests()};

	cmoon::test::text_test_runner runner{std::cout};

	return std::ranges::any_of(runner.run(suite), [](const auto& r) { return !r.passed(); });
}