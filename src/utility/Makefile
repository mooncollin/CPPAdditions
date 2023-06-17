override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.utility,cmoon.utility.owner \
									   cmoon.utility.throw_on_error \
									   cmoon.utility.extent_type \
									   cmoon.utility.stopwatch \
									   cmoon.utility.as_unsigned \
									   cmoon.utility.copyable_box \
									   cmoon.utility.decay_copy \
									   cmoon.utility)
	$(call build-library)


$(call add-build-module,cmoon.utility,utility.ixx, \
									  cmoon.utility.owner \
									  cmoon.utility.throw_on_error \
									  cmoon.utility.extent_type \
									  cmoon.utility.stopwatch \
									  cmoon.utility.as_unsigned \
									  cmoon.utility.decay_copy \
									  cmoon.utility.copyable_box)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,utility.ixx)

$(call add-build-module,cmoon.utility.owner,owner.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,owner.ixx)

$(call add-build-module,cmoon.utility.throw_on_error,throw_on_error.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,throw_on_error.ixx)

$(call add-build-module,cmoon.utility.extent_type,extent_type.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,extent_type.ixx)

$(call add-build-module,cmoon.utility.stopwatch,stopwatch.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,stopwatch.ixx)

$(call add-build-module,cmoon.utility.as_unsigned,as_unsigned.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,as_unsigned.ixx)

$(call add-build-module,cmoon.utility.copyable_box,copyable_box.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,copyable_box.ixx)

$(call add-build-module,cmoon.utility.decay_copy,decay_copy.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,decay_copy.ixx)

# TESTS-----------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.utility,cmoon.tests.utility)
	$(call build-library)

$(call add-build-module,cmoon.tests.utility,$(tests_directory)/utility.ixx, \
												 cmoon.utility \
												 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,utility.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.tests.utility \
								cmoon.utility \
								cmoon.concepts \
								cmoon.test \
								cmoon.ranges \
								cmoon.tuple \
								cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

include $(CURDIR)/$(level)/Makefile_template_end