export module cmoon.benchmarking.text_benchmark_runner;

import std.core;

import cmoon.benchmarking.benchmark;
import cmoon.benchmarking.benchmark_result;
import cmoon.benchmarking.benchmark_suite;

namespace cmoon::benchmarking
{
	class dummy_result_output
	{
		public:
			using difference_type = std::ptrdiff_t;

			dummy_result_output& operator*() noexcept
			{
				return *this;
			}

			dummy_result_output& operator=(std::pair<std::string, const benchmark_result&>)
			{
				return *this;
			}

			dummy_result_output& operator++()
			{
				return *this;
			}

			dummy_result_output operator++(int)
			{
				return *this;
			}
	};

	export
	template<class CharT, class Traits>
	class text_benchmark_runner
	{
		public:
			text_benchmark_runner(std::basic_ostream<CharT, Traits>& out)
				: out_{out} {}

			void run(benchmark& bench)
			{
				benchmark_suite suite;
				suite.add_benchmark<benchmark>(bench);
				run(suite);
			}

			template<std::output_iterator<std::pair<std::string, benchmark_result>> OutputIt = dummy_result_output>
			OutputIt run(benchmark_suite& suite, OutputIt out = {})
			{
				out_ << std::format(out_.getloc(),
									"[==========] Running {} benchmark{}\n", std::ranges::size(suite), plural(std::ranges::size(suite)));

				for (auto bench : suite)
				{
					out_ << std::format(out_.getloc(),
										"[ RUN      ] {} ({} run{}, {} iteration{} per run)\n",
										bench->name(),
										bench->runs(),
										plural(bench->runs()),
										bench->iterations_per_run(),
										plural(bench->iterations_per_run()));

					auto results {run_benchmark(*bench)};

					const auto average_run_time {results.average_run_time()};
					const auto fastest_run {results.fastest_run()};
					const auto slowest_run {results.slowest_run()};
						
					out_ << std::format(out_.getloc(),
										"[     DONE ] {} (", bench->name());
					pretty_print_duration(results.total_run_time());
					out_ << ")\n";

					out_ << "[   RUNS   ]        Average time: ";
					pretty_print_duration(average_run_time);
					out_ << "\n                         Fastest: ";
					pretty_print_duration(fastest_run.total_time());
					out_ << "\n                         Slowest: ";
					pretty_print_duration(slowest_run.total_time());
					out_ << "\n\n";

					const auto run_average_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(average_run_time)};
					const auto run_best_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(fastest_run.total_time())};
					const auto run_worst_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(slowest_run.total_time())};

					out_ << std::format(out_.getloc(),
									    "             Average performance: {:.5f} runs/s\n"
										"                Best performance: {:.5f} runs/s\n"
										"               Worst performance: {:.5f} runs/s\n",
										run_average_performance,
										run_best_performance,
										run_worst_performance);

					const auto average_iteration_time {results.average_iteration_time()};
					const auto fastest_iteration {results.fastest_iteration()};
					const auto slowest_iteration {results.slowest_iteration()};

					out_ << "[ITERATIONS]        Average time: ";
					pretty_print_duration(average_iteration_time);
					out_ << "\n                         Fastest: ";
					pretty_print_duration(fastest_iteration);
					out_ << "\n                         Slowest: ";
					pretty_print_duration(slowest_iteration);
					out_ << "\n\n";

					const auto iteration_average_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(average_iteration_time)};
					const auto iteration_best_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(fastest_iteration)};
					const auto iteration_worst_performance {std::chrono::duration<double>{1} / std::chrono::duration_cast<std::chrono::duration<double>>(slowest_iteration)};

					out_ << std::format(out_.getloc(),
										"             Average performance: {:.5f} iterations/s\n"
										"                Best performance: {:.5f} iterations/s\n"
										"               Worst performance: {:.5f} iterations/s\n",
										iteration_average_performance,
										iteration_best_performance,
										iteration_worst_performance);

					*out = std::make_pair(bench->name(), std::move(results));
					++out;
				}

				return out;
			}
		private:
			std::basic_ostream<CharT, Traits>& out_;

			[[nodiscard]] static constexpr std::string_view plural(std::size_t s) noexcept
			{
				if (s == 1)
				{
					return "";
				}

				return "s";
			}

			void pretty_print_duration(const std::chrono::nanoseconds& ns)
			{
				if (const auto hours {std::chrono::duration_cast<std::chrono::duration<double, typename std::chrono::hours::period>>(ns)}; 
					hours.count() > 1)
				{
					out_ << hours;
					out_ << std::format(out_.getloc(),
										"{} h{:%Q %q}", hours.count(), hours);
				}
				else
				{
					const auto minutes {std::chrono::duration_cast<std::chrono::duration<double, typename std::chrono::minutes::period>>(ns)};
					if (minutes.count() > 1)
					{
						out_ << std::format(out_.getloc(),
											"{:%Q %q}", minutes);
					}
					else
					{
						const auto seconds {std::chrono::duration_cast<std::chrono::duration<double, typename std::chrono::seconds::period>>(ns)};
						if (seconds.count() > 1)
						{
							out_ << std::format(out_.getloc(),
												"{:%Q %q}", seconds);
						}
						else
						{
							const auto milliseconds {std::chrono::duration_cast<std::chrono::duration<double, typename std::chrono::milliseconds::period>>(ns)};
							if (milliseconds.count() > 1)
							{
								out_ << std::format(out_.getloc(),
													"{:%Q %q}", milliseconds);
							}
							else
							{
								out_ << std::format(out_.getloc(),
													"{:%Q %q}", ns);
							}
						}
					}
				}
			}
	};
}