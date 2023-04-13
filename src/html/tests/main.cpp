import std.core;

import cmoon.test;
import cmoon.tests.html;
import cmoon.html;

int main()
{
	auto suite {cmoon::tests::html::get_tests()};

	cmoon::test::text_test_runner runner{std::cout};

	return std::ranges::any_of(runner.run(suite), [](const auto& r) { return !r.passed(); });
}