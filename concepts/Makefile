include $(TEMPLATE_BEGIN)

cmoon_type_traits_library 	=$(call get-library,type_traits)
cmoon_test_library 			=$(call get-library,test)
cmoon_concepts_library 		=$(call get-library,concepts)
cmoon_utility_library 		=$(call get-library,utility)
cmoon_ranges_library 		=$(call get-library,ranges)
cmoon_tuple_library 		=$(call get-library,tuple)
cmoon_scope_library 		=$(call get-library,scope)

$(call add-build-library,cmoon.concepts,cmoon.concepts)
	$(call build-library)

$(call add-build-library,cmoon.tests.concepts,cmoon.tests.concepts)
	$(call build-library)

$(call add-build-module,cmoon.concepts,concepts.ixx)
	$(call make-library-module,cmoon.type_traits,$(cmoon_type_traits_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call src-file,concepts.ixx)

$(call add-build-module,cmoon.tests.concepts,$(tests_directory)/concepts.ixx \
											 $(build_directory)/cmoon.concepts.ifc)
	$(call make-library-module,cmoon.test,$(cmoon_test_library))
	$(call make-library-module,cmoon.type_traits,$(cmoon_type_traits_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir) \
		$(call test-file,concepts.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.concepts.lib \
								$(build_directory)/cmoon.concepts.lib)
	$(call make-library-lib,cmoon.test,$(cmoon_test_library))
	$(call make-library-lib,cmoon.utility,$(cmoon_utility_library))
	$(call make-library-lib,cmoon.ranges,$(cmoon_ranges_library))
	$(call make-library-lib,cmoon.tuple,$(cmoon_tuple_library))
	$(call make-library-lib,cmoon.scope,$(cmoon_scope_library))
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.concepts) \
		$(call add-module-lib,cmoon.tests.concepts) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)