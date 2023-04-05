override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.concepts,cmoon.concepts)
	$(call build-library)

$(call add-build-module-impl,cmoon.concepts,concepts.ixx, \
											cmoon.type_traits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,concepts.ixx)

# TESTS-------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.concepts,cmoon.tests.concepts)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.concepts,$(tests_directory)/concepts.ixx, \
											 	  cmoon.concepts \
												  cmoon.type_traits \
												  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,concepts.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.tests.concepts \
								cmoon.concepts \
								cmoon.type_traits \
								cmoon.test \
								cmoon.utility \
								cmoon.tuple \
								cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	@$(bin_directory)/tests.exe

include $(CURDIR)/$(level)/Makefile_template_end