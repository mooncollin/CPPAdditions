override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.fixed_valarray,cmoon.fixed_valarray.underlying \
										 	   cmoon.fixed_valarray.expressions \
										 	   cmoon.fixed_valarray)
	$(call build-library)

$(call add-build-module-impl,cmoon.fixed_valarray,fixed_valarray.ixx, \
							 					  cmoon.fixed_valarray.expressions \
							 					  cmoon.fixed_valarray.underlying)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,fixed_valarray.ixx)

$(call add-build-module-impl,cmoon.fixed_valarray.expressions,expressions.ixx, \
														 	  cmoon.type_traits \
														 	  cmoon.meta)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,expressions.ixx)

$(call add-build-module-impl,cmoon.fixed_valarray.underlying,underlying.ixx, \
															 cmoon.simd)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,underlying.ixx)

#-------------------------------

$(call add-bin-target,main.exe,main.cpp, \
							   cmoon.fixed_valarray \
							   cmoon.meta)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call src-file,main.cpp)

main: $(bin_directory)/main.exe
	@$(bin_directory)/main.exe


# TESTS-----------------------------------------------------------------

$(call add-build-library,cmoon.tests.fixed_valarray,cmoon.tests.fixed_valarray)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.fixed_valarray,$(tests_directory)/fixed_valarray.ixx, \
														cmoon.fixed_valarray \
											  			cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,fixed_valarray.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.tests.fixed_valarray \
								cmoon.fixed_valarray \
								cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(CURDIR)/$(level)/Makefile_template_end