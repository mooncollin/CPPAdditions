export module cmoon.test.text_test_runner;

import std.core;

import cmoon.utility;
import cmoon.scope;
import cmoon.ranges;

import cmoon.test.test_case;
import cmoon.test.test_suite;
import cmoon.test.test_result;

namespace cmoon::test
{
	export
	class text_test_runner
	{
		public:
			text_test_runner(std::ostream& out) noexcept
				: output_{out} {}

			test_result run(test_case& t_case)
			{
				if (!t_case.name().empty())
				{
					output_.get() << "\nRunning test case: ";
					output_.get() << t_case.name();
					output_.get() << '\n';
				}
				print_header();
				stopwatch.reset();
				const auto result {t_case.run()};
				const auto duration {stopwatch.get_elapsed_time()};
				print_test_result(result);

				output_.get() << "=======================================\n";
				print_footer(duration);

				if (result.passed())
				{
					output_.get() << "\nOK! 1 passed.\n\n";
				}
				else
				{
					output_.get() << "\nFAILED! 1 ";
					if (!result.errors().empty())
					{
						output_.get() << "error.\n\n";
					}
					else
					{
						output_.get() << "failure.\n\n";
					}
				}

				return result;
			}

			std::vector<test_result> run(test_suite& t_suite)
			{
				std::vector<test_result> results;
				std::size_t num_passed {0};
				std::size_t num_errored {0};
				std::size_t num_failed {0};

				if (!t_suite.name().empty())
				{
					output_.get() << "Running test suite: ";
					output_.get() << t_suite.name();
					output_.get() << '\n';
				}
				print_header();
				stopwatch.reset();
				for (auto& t_case : t_suite)
				{
					results.push_back(t_case.run());
					if (!results.back().errors().empty())
					{
						++num_errored;
						output_.get() << 'E';
					}
					else if (!results.back().failures().empty())
					{
						++num_failed;
						output_.get() << 'F';
					}
					else
					{
						++num_passed;
						output_.get() << '.';
					}
				}
				const auto duration {stopwatch.get_elapsed_time()};

				output_.get() << "\n\n=======================================\n";

				for (const auto& [result, test_case] : cmoon::ranges::views::zip(results, t_suite))
				{
					if (!result.passed())
					{
						output_.get() << '\n';
						output_.get() << test_case.name();
						output_.get() << '\n';
						print_test_result(result);
					}
				}

				output_.get() << "=======================================\n";
				print_footer(duration);

				if (num_passed == results.size())
				{
					output_.get() << "\nOK!";
				}
				else
				{
					output_.get() << "\nFAILED!";
				}

				if (num_passed != 0)
				{
					output_.get() << ' ';
					output_.get() << num_passed;
					output_.get() << " passed";
				}
				if (num_errored != 0)
				{
					output_.get() << ' ';
					output_.get() << num_errored;
					output_.get() << " errored";
				}
				if (num_failed != 0)
				{
					output_.get() << ' ';
					output_.get() << num_failed;
					output_.get() << " failed";
				}
				output_.get() << '\n';

				return results;
			}
		private:
			void print_header()
			{
				output_.get() << "Starting testing at ";
				output_.get() << std::format(output_.get().getloc(), "{:%F %T}",
									   std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()});
				output_.get() << "\n\n";
			}

			template<class Duration>
			void print_footer(const Duration& duration)
			{
				output_.get() << "Ending testing at ";
				output_.get() << std::format(output_.get().getloc(), "{:%F %T}",
									   std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()});
				output_.get() << " : ";

				cmoon::scope_exit reset_fmt {[this, before_fmt = output_.get().flags()] {
					output_.get().setf(before_fmt);
				}};
				
				output_.get().setf(std::ios::fixed);

				if (const std::chrono::duration<double> seconds {duration};
					seconds.count() > 1)
				{
					output_.get().precision(3);
					output_.get() << seconds;
				}
				else if (const std::chrono::duration<double, std::milli> milliseconds {duration};
						 milliseconds.count() > 1)
				{
					output_.get().precision(3);
					output_.get() << milliseconds;
				}
				else
				{
					const std::chrono::nanoseconds nanoseconds {duration};
					output_.get() << nanoseconds;
				}
			}

			void print_test_result(const test_result& result)
			{
				if (!result.errors().empty())
				{
					output_.get() << "Errors:\n";

					for (const auto& error : result.errors())
					{
						output_.get() << error.what()
									  << '\n';
					}
				}

				if (!result.failures().empty())
				{
					output_.get() << "Failures:\n";

					for (const auto& failure : result.failures())
					{
						output_.get() << failure.what()
									  << '\n';
					}
				}
			}

			std::reference_wrapper<std::ostream> output_;
			cmoon::stopwatch stopwatch;
	};
}