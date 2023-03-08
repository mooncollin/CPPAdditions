include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.string.lib)

$(eval $(call import-library,concepts))
$(eval $(call import-library,platform))
$(eval $(call import-library,test))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))
$(eval $(call import-library,scope))
$(eval $(call import-library,utility))

$(call add-build-library,cmoon.string,cmoon.string.platform \
									  cmoon.string.character \
									  cmoon.string.algorithm \
									  cmoon.string)
	$(call build-library)

$(call add-build-library,cmoon.tests.string,cmoon.tests.string.algorithm \
											cmoon.tests.string)
	$(call build-library)

$(call add-build-module-impl,cmoon.string,string.ixx \
									 $(build_directory)/cmoon.string.platform.ifc \
									 $(build_directory)/cmoon.string.character.ifc \
									 $(build_directory)/cmoon.string.algorithm.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,string.ixx)

$(call add-build-module-impl,cmoon.string.platform,platform.ixx, \
												   	cmoon.platform)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_platform_library)) \
		$(call src-file,platform.ixx)

$(call add-build-module-impl,cmoon.string.character,character.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,character.ixx)

$(call add-build-module-impl,cmoon.string.algorithm,algorithm.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,algorithm.ixx)

$(call add-build-module-impl,cmoon.tests.string.algorithm,$(tests_directory)/algorithm.ixx \
													 	  $(build_directory)/cmoon.string.ifc, \
														  	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir) \
		$(call test-file,algorithm.ixx)

$(call add-build-module-impl,cmoon.tests.string,$(tests_directory)/string.ixx \
										   		$(build_directory)/cmoon.tests.string.algorithm.ifc, \
													cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir) \
		$(call test-file,string.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.string.lib \
								$(build_directory)/cmoon.string.lib, \
									cmoon.concepts \
									cmoon.test \
									cmoon.ranges \
									cmoon.tuple \
									cmoon.scope \
									cmoon.utility)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.string) \
		$(call add-module-lib,cmoon.tests.string) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)