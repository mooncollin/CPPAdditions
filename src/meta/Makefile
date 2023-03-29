include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.meta.lib)

$(eval $(call import-library,type_traits))
$(eval $(call import-library,concepts))
$(eval $(call import-library,test))
$(eval $(call import-library,utility))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))

$(call add-build-library,cmoon.meta,cmoon.meta.choice_t \
									cmoon.meta.type_list \
									cmoon.meta.value_list \
									cmoon.meta)
	$(call build-library)

$(call add-build-library,cmoon.tests.meta,cmoon.tests.meta.type_list \
										  cmoon.tests.meta)
	$(call build-library)

$(call add-build-module-impl,cmoon.meta,meta.ixx \
									    $(build_directory)/cmoon.meta.choice_t.ifc \
									    $(build_directory)/cmoon.meta.type_list.ifc \
									    $(build_directory)/cmoon.meta.value_list.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,meta.ixx)

$(call add-build-module-impl,cmoon.meta.choice_t,choice_t.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,choice_t.ixx)

$(call add-build-module-impl,cmoon.meta.type_list,type_list.ixx, \
													cmoon.type_traits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call src-file,type_list.ixx)

$(call add-build-module-impl,cmoon.meta.value_list,value_list.ixx \
												   $(build_directory)/cmoon.meta.type_list.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call src-file,value_list.ixx)

$(call add-build-module-impl,cmoon.tests.meta,$(tests_directory)/meta.ixx \
											  $(build_directory)/cmoon.tests.meta.type_list.ifc, \
											  	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir) \
		$(call test-file,meta.ixx)

$(call add-build-module-impl,cmoon.tests.meta.type_list,$(tests_directory)/type_list.ixx \
													 	$(build_directory)/cmoon.meta.ifc, \
															cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir) \
		$(call test-file,type_list.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.meta.lib \
								$(build_directory)/cmoon.tests.meta.lib, \
									cmoon.test \
									cmoon.concepts \
									cmoon.utility \
									cmoon.ranges)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.tests.meta) \
		$(call add-module-lib,cmoon.type_traits,$(cmoon_type_traits_library)) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.concepts,$(cmoon_concepts_library)) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)