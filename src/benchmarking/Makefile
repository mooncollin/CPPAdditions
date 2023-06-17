override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.benchmarking,cmoon.benchmarking.do_not_optimize \
											cmoon.benchmarking.run_result \
											cmoon.benchmarking.benchmark_result \
											cmoon.benchmarking.benchmark \
											cmoon.benchmarking.benchmark_function \
											cmoon.benchmarking.noop_benchmark \
											cmoon.benchmarking.benchmark_suite \
											cmoon.benchmarking.text_benchmark_runner \
											cmoon.benchmarking.benchmark_compare \
											cmoon.benchmarking)
	$(call build-library)

$(call add-build-module,cmoon.benchmarking,benchmarking.ixx, \
										   		cmoon.benchmarking.do_not_optimize \
										   		cmoon.benchmarking.run_result \
										   		cmoon.benchmarking.benchmark_result \
										   		cmoon.benchmarking.benchmark \
										   		cmoon.benchmarking.benchmark_function \
										   		cmoon.benchmarking.noop_benchmark \
										   		cmoon.benchmarking.benchmark_suite \
										   		cmoon.benchmarking.text_benchmark_runner \
										   		cmoon.benchmarking.benchmark_compare)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmarking.ixx)

$(call add-build-module,cmoon.benchmarking.do_not_optimize,do_not_optimize.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,do_not_optimize.ixx)

$(call add-build-module,cmoon.benchmarking.run_result,run_result.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,run_result.ixx)

$(call add-build-module,cmoon.benchmarking.benchmark_result,benchmark_result.ixx, \
																 cmoon.benchmarking.run_result)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmark_result.ixx)

$(call add-build-module,cmoon.benchmarking.benchmark,benchmark.ixx, \
														  cmoon.benchmarking.benchmark_result \
														  cmoon.utility)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmark.ixx)

$(call add-build-module,cmoon.benchmarking.benchmark_function,benchmark_function.ixx, \
																   cmoon.benchmarking.benchmark)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmark_function.ixx)

$(call add-build-module,cmoon.benchmarking.noop_benchmark,noop_benchmark.ixx, \
															   cmoon.benchmarking.benchmark \
															   cmoon.benchmarking.do_not_optimize)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,noop_benchmark.ixx)

$(call add-build-module,cmoon.benchmarking.benchmark_suite,benchmark_suite.ixx, \
																cmoon.benchmarking.benchmark)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmark_suite.ixx)

$(call add-build-module,cmoon.benchmarking.text_benchmark_runner,text_benchmark_runner.ixx, \
																	  cmoon.benchmarking.benchmark \
																	  cmoon.benchmarking.benchmark_result \
																	  cmoon.benchmarking.benchmark_suite)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,text_benchmark_runner.ixx)

$(call add-build-module,cmoon.benchmarking.benchmark_compare,benchmark_compare.ixx, \
																  cmoon.benchmarking.benchmark_result \
																  cmoon.benchmarking.benchmark \
																  cmoon.benchmarking.benchmark_suite \
																  cmoon.benchmarking.noop_benchmark)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,benchmark_compare.ixx)

# TESTS-----------------------------------------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.benchmarking,cmoon.tests.benchmarking.run_result \
												  cmoon.tests.benchmarking.benchmark_result \
												  cmoon.tests.benchmarking.benchmark_function \
												  cmoon.tests.benchmarking.noop_benchmark \
												  cmoon.tests.benchmarking)
	$(call build-library)

$(call add-build-module,cmoon.tests.benchmarking,$(tests_directory)/benchmarking.ixx, \
											 	 	  cmoon.benchmarking \
												 	  cmoon.tests.benchmarking.run_result \
												 	  cmoon.tests.benchmarking.benchmark_result \
												 	  cmoon.tests.benchmarking.benchmark_function \
												 	  cmoon.tests.benchmarking.noop_benchmark \
													  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,benchmarking.ixx)

$(call add-build-module,cmoon.tests.benchmarking.benchmark_function,$(tests_directory)/benchmark_function.ixx, \
											 							 cmoon.benchmarking \
																		 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,benchmark_function.ixx)

$(call add-build-module,cmoon.tests.benchmarking.benchmark_result,$(tests_directory)/benchmark_result.ixx, \
											 					  	   cmoon.benchmarking \
																	   cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,benchmark_result.ixx)

$(call add-build-module,cmoon.tests.benchmarking.noop_benchmark,$(tests_directory)/noop_benchmark.ixx, \
											 						 cmoon.benchmarking \
																	 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,noop_benchmark.ixx)

$(call add-build-module,cmoon.tests.benchmarking.run_result,$(tests_directory)/run_result.ixx, \
											 					 cmoon.benchmarking \
																 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,run_result.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.benchmarking \
								cmoon.tests.benchmarking \
								cmoon.test \
								cmoon.concepts \
								cmoon.utility \
								cmoon.ranges \
								cmoon.tuple \
								cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(CURDIR)/$(level)/Makefile_template_end