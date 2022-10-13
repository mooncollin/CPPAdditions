import std.core;

import cmoon.test;

import cmoon.tests.benchmarking;

int main()
{
	auto suite {cmoon::tests::benchmarking::get_tests()};

	cmoon::test::text_test_runner runner{std::cout};

	return std::ranges::any_of(runner.run(suite), [](const auto& r) { return !r.passed(); });
}