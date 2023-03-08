export module cmoon.tests.benchmarking;
export import cmoon.tests.benchmarking.run_result;
export import cmoon.tests.benchmarking.benchmark_result;
export import cmoon.tests.benchmarking.benchmark_function;
export import cmoon.tests.benchmarking.noop_benchmark;

import std.core;

import cmoon.test;

namespace cmoon::tests::benchmarking
{
	export
	cmoon::test::test_suite get_tests()
	{
		cmoon::test::test_suite suite{"Benchmarking library tests"};
		suite.add_test_case<run_result_test>();
		suite.add_test_case<benchmark_result_test>();
		suite.add_test_case<benchmark_function_test>();
		suite.add_test_case<noop_benchmark_test>();

		return std::move(suite);
	}
}