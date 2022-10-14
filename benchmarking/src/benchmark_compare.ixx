export module cmoon.benchmarking.benchmark_compare;

import std.core;

import cmoon.benchmarking.benchmark_result;
import cmoon.benchmarking.benchmark;
import cmoon.benchmarking.benchmark_suite;
import cmoon.benchmarking.noop_benchmark;

namespace cmoon::benchmarking
{
	export
	class benchmark_compare
	{
		using noop_t = std::chrono::duration<double, std::nano>;

		public:
			using value_type = std::pair<std::string, const benchmark_result&>;

			benchmark_compare() noexcept
				: noop_average{std::max(std::chrono::duration_cast<noop_t>(run_benchmark(noop_benchmark{}).average_iteration_time()),
										noop_t::min())} {}

			void push_back(value_type p)
			{
				add_result(
					std::move(p.first),
					p.second
				);
			}

			void add_result(std::string name,
							const benchmark_result& result)
			{
				results_.emplace_back(
					std::move(name),
					result.average_iteration_time() / noop_average
				);
			}

			void run(benchmark& bench)
			{
				add_result(bench.name(),
						   run_benchmark(bench));
			}

			void run(benchmark&& bench)
			{
				run(bench);
			}

			void run(benchmark_suite& suite)
			{
				for (auto bench : suite)
				{
					run(*bench);
				}
			}

			void run(benchmark_suite&& suite)
			{
				run(suite);
			}

			[[nodiscard]] auto begin() const noexcept
			{
				return std::ranges::begin(results_);
			}

			[[nodiscard]] auto end() const noexcept
			{
				return std::ranges::end(results_);
			}

			template<class CharT, class Traits>
			friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const benchmark_compare& comp)
			{
				if (std::ranges::size(comp.results_) > 0)
				{
					const auto right_padding_amount {
						std::ranges::max(comp.results_ |
										 std::views::keys |
										 std::views::transform(std::ranges::size))
					};

					os << "Results (CPU time / Noop time):\n\n";
					for (const auto& [name, result] : comp.results_)
					{
						os << std::format(os.getloc(),
										  "{: <{}}: {:.4f}\n", name, right_padding_amount, result);
					}

					os << '\n';

					if (std::size(comp.results_) > 1)
					{
						for (auto it {std::ranges::cbegin(comp.results_)}; it != std::ranges::cend(comp.results_); ++it)
						{
							os << it->first << ":\n";
							for (auto it2 {std::ranges::cbegin(comp.results_)}; it2 != std::ranges::cend(comp.results_); ++it2)
							{
								if (it == it2)
								{
									continue;
								}

								const auto minmax {std::minmax(it->second, it2->second)};
								if (minmax.second - minmax.first <= 5.0)
								{
									os << "  Roughly the same as ";
								}
								else
								{
									const auto scale {minmax.second / minmax.first};
									os << std::format("  {:.2f}x", scale);
									if (it->second > it2->second)
									{
										os << " slower than ";
									}
									else
									{
										os << " faster than ";
									}
								}
								os << it2->first << "\n\n";
							}
						}
					}
				}
				else
				{
					os << "No benchmark results\n";
				}

				return os;
			}
		private:
			noop_t noop_average;
			std::deque<std::pair<std::string, double>> results_;
	};
}