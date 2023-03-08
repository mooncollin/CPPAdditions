include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.benchmarking.lib)

$(eval $(call import-library,concepts))
$(eval $(call import-library,test))
$(eval $(call import-library,utility))
$(eval $(call import-library,type_traits))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))
$(eval $(call import-library,scope))

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

$(call add-build-module-impl,cmoon.benchmarking,benchmarking.ixx \
										   		$(build_directory)/cmoon.benchmarking.do_not_optimize.ifc \
										   		$(build_directory)/cmoon.benchmarking.run_result.ifc \
										   		$(build_directory)/cmoon.benchmarking.benchmark_result.ifc \
										   		$(build_directory)/cmoon.benchmarking.benchmark.ifc \
										   		$(build_directory)/cmoon.benchmarking.benchmark_function.ifc \
										   		$(build_directory)/cmoon.benchmarking.noop_benchmark.ifc \
										   		$(build_directory)/cmoon.benchmarking.benchmark_suite.ifc \
										   		$(build_directory)/cmoon.benchmarking.text_benchmark_runner.ifc \
										   		$(build_directory)/cmoon.benchmarking.benchmark_compare.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,benchmarking.ixx)

$(call add-build-module-impl,cmoon.benchmarking.do_not_optimize,do_not_optimize.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,do_not_optimize.ixx)

$(call add-build-module-impl,cmoon.benchmarking.run_result,run_result.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,run_result.ixx)

$(call add-build-module-impl,cmoon.benchmarking.benchmark_result,benchmark_result.ixx \
																 $(build_directory)/cmoon.benchmarking.run_result.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,benchmark_result.ixx)

$(call add-build-module-impl,cmoon.benchmarking.benchmark,benchmark.ixx \
														  $(build_directory)/cmoon.benchmarking.benchmark_result.ifc, \
														  	cmoon.utility)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call src-file,benchmark.ixx)

$(call add-build-module-impl,cmoon.benchmarking.benchmark_function,benchmark_function.ixx \
																   $(build_directory)/cmoon.benchmarking.benchmark.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,benchmark_function.ixx)

$(call add-build-module-impl,cmoon.benchmarking.noop_benchmark,noop_benchmark.ixx \
															   $(build_directory)/cmoon.benchmarking.benchmark.ifc \
															   $(build_directory)/cmoon.benchmarking.do_not_optimize.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,noop_benchmark.ixx)

$(call add-build-module-impl,cmoon.benchmarking.benchmark_suite,benchmark_suite.ixx \
																$(build_directory)/cmoon.benchmarking.benchmark.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,benchmark_suite.ixx)

$(call add-build-module-impl,cmoon.benchmarking.text_benchmark_runner,text_benchmark_runner.ixx \
																	  $(build_directory)/cmoon.benchmarking.benchmark.ifc \
																	  $(build_directory)/cmoon.benchmarking.benchmark_result.ifc \
																	  $(build_directory)/cmoon.benchmarking.benchmark_suite.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,text_benchmark_runner.ixx)

$(call add-build-module-impl,cmoon.benchmarking.benchmark_compare,benchmark_compare.ixx \
																  $(build_directory)/cmoon.benchmarking.benchmark_result.ifc \
																  $(build_directory)/cmoon.benchmarking.benchmark.ifc \
																  $(build_directory)/cmoon.benchmarking.benchmark_suite.ifc \
																  $(build_directory)/cmoon.benchmarking.noop_benchmark.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,benchmark_compare.ixx)

## Tests

$(call add-build-library,cmoon.tests.benchmarking,cmoon.tests.benchmarking.run_result \
												  cmoon.tests.benchmarking.benchmark_result \
												  cmoon.tests.benchmarking.benchmark_function \
												  cmoon.tests.benchmarking.noop_benchmark \
												  cmoon.tests.benchmarking)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.benchmarking,$(tests_directory)/benchmarking.ixx \
											 	 	  $(build_directory)/cmoon.benchmarking.ifc \
												 	  $(build_directory)/cmoon.tests.benchmarking.run_result.ifc \
												 	  $(build_directory)/cmoon.tests.benchmarking.benchmark_result.ifc \
												 	  $(build_directory)/cmoon.tests.benchmarking.benchmark_function.ifc \
												 	  $(build_directory)/cmoon.tests.benchmarking.noop_benchmark.ifc, \
													  	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call test-file,benchmarking.ixx)

$(call add-build-module-impl,cmoon.tests.benchmarking.benchmark_function,$(tests_directory)/benchmark_function.ixx \
											 							 $(build_directory)/cmoon.benchmarking.ifc, \
																		 	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call test-file,benchmark_function.ixx)

$(call add-build-module-impl,cmoon.tests.benchmarking.benchmark_result,$(tests_directory)/benchmark_result.ixx \
											 					  	   $(build_directory)/cmoon.benchmarking.ifc, \
																	   	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call test-file,benchmark_result.ixx)

$(call add-build-module-impl,cmoon.tests.benchmarking.noop_benchmark,$(tests_directory)/noop_benchmark.ixx \
											 						 $(build_directory)/cmoon.benchmarking.ifc, \
																	 	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call test-file,noop_benchmark.ixx)

$(call add-build-module-impl,cmoon.tests.benchmarking.run_result,$(tests_directory)/run_result.ixx \
											 					 $(build_directory)/cmoon.benchmarking.ifc, \
																 	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call test-file,run_result.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.benchmarking.lib \
								$(build_directory)/cmoon.benchmarking.lib, \
									cmoon.test \
									cmoon.concepts \
									cmoon.utility \
									cmoon.ranges \
									cmoon.tuple \
									cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-lib,cmoon.benchmarking) \
		$(call add-module-lib,cmoon.tests.benchmarking) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.concepts,$(cmoon_concepts_library)) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)