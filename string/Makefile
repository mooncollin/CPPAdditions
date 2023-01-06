include $(TEMPLATE_BEGIN)

cmoon_concepts_library =$(call get-library,concepts)
cmoon_platform_library =$(call get-library,platform)
cmoon_test_library     =$(call get-library,test)
cmoon_ranges_library   =$(call get-library,ranges)
cmoon_tuple_library    =$(call get-library,tuple)
cmoon_scope_library    =$(call get-library,scope)
cmoon_utility_library  =$(call get-library,utility)

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

$(call add-build-module-impl,cmoon.string.platform,platform.ixx)
	$(call make-library-module,cmoon.platform,$(cmoon_platform_library))
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
													 	  $(build_directory)/cmoon.string.ifc)
	$(call make-library-module,cmoon.test,$(cmoon_test_library))
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir) \
		$(call test-file,algorithm.ixx)

$(call add-build-module-impl,cmoon.tests.string,$(tests_directory)/string.ixx \
										   		$(build_directory)/cmoon.tests.string.algorithm.ifc)
	$(call make-library-module,cmoon.test,$(cmoon_test_library))
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir) \
		$(call test-file,string.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.string.lib \
								$(build_directory)/cmoon.string.lib)
	$(call make-library-lib,cmoon.concepts,$(cmoon_concepts_library))
	$(call make-library-lib,cmoon.test,$(cmoon_test_library))
	$(call make-library-lib,cmoon.ranges,$(cmoon_ranges_library))
	$(call make-library-lib,cmoon.tuple,$(cmoon_tuple_library))
	$(call make-library-lib,cmoon.scope,$(cmoon_scope_library))
	$(call make-library-lib,cmoon.utility,$(cmoon_utility_library))
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