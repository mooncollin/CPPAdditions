include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.concepts.lib)

$(eval $(call import-library,type_traits))
$(eval $(call import-library,test))
$(eval $(call import-library,utility))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))
$(eval $(call import-library,scope))

$(call add-build-library,cmoon.concepts,cmoon.concepts)
	$(call build-library)

$(call add-build-library,cmoon.tests.concepts,cmoon.tests.concepts)
	$(call build-library)

$(call add-build-module-impl,cmoon.concepts,concepts.ixx, \
												cmoon.type_traits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call src-file,concepts.ixx)

$(call add-build-module-impl,cmoon.tests.concepts,$(tests_directory)/concepts.ixx \
											 	  $(build_directory)/cmoon.concepts.ifc, \
												  	cmoon.type_traits \
													cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir) \
		$(call test-file,concepts.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.concepts.lib \
								$(build_directory)/cmoon.concepts.lib, \
									cmoon.type_traits \
									cmoon.test \
									cmoon.utility \
									cmoon.ranges \
									cmoon.tuple \
									cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.concepts) \
		$(call add-module-lib,cmoon.tests.concepts) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)