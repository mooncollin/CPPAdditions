override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.named_tuple,cmoon.named_tuple)
	$(call build-library)

$(call add-build-module,cmoon.named_tuple,named_tuple.ixx, \
									      cmoon.meta \
										  cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,named_tuple.ixx)

# TESTS------------------------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.named_tuple,cmoon.tests.named_tuple)
	$(call build-library)

$(call add-build-module,cmoon.tests.named_tuple,$(tests_directory)/named_tuple.ixx, \
												cmoon.named_tuple \
											  	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,named_tuple.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.named_tuple \
								cmoon.tests.named_tuple \
								cmoon.test \
								cmoon.concepts \
								cmoon.utility)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

include $(CURDIR)/$(level)/Makefile_template_end