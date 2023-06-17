override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.meta,cmoon.meta.choice_t \
									cmoon.meta.type_list \
									cmoon.meta.value_list \
									cmoon.meta)
	$(call build-library)


$(call add-build-module,cmoon.meta,meta.ixx, \
								   cmoon.meta.choice_t \
								   cmoon.meta.type_list \
								   cmoon.meta.value_list)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,meta.ixx)

$(call add-build-module,cmoon.meta.choice_t,choice_t.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,choice_t.ixx)

$(call add-build-module,cmoon.meta.type_list,type_list.ixx, \
											 cmoon.type_traits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,type_list.ixx)

$(call add-build-module,cmoon.meta.value_list,value_list.ixx, \
											  cmoon.meta.type_list)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,value_list.ixx)

# TESTS------------------------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.meta,cmoon.tests.meta.value_list \
										  cmoon.tests.meta.type_list \
										  cmoon.tests.meta)
	$(call build-library)

$(call add-build-module,cmoon.tests.meta,$(tests_directory)/meta.ixx, \
										 cmoon.tests.meta.type_list \
										 cmoon.tests.meta.value_list \
										 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,meta.ixx)

$(call add-build-module,cmoon.tests.meta.type_list,$(tests_directory)/type_list.ixx, \
												   cmoon.meta \
												   cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,type_list.ixx)

$(call add-build-module,cmoon.tests.meta.value_list,$(tests_directory)/value_list.ixx, \
												   cmoon.meta \
												   cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,value_list.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.meta \
								cmoon.tests.meta \
								cmoon.test \
								cmoon.concepts \
								cmoon.utility \
								cmoon.ranges)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

include $(CURDIR)/$(level)/Makefile_template_end