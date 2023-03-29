include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.fixed_valarray.lib)

$(eval $(call import-library,test))
$(eval $(call import-library,utility))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))
$(eval $(call import-library,scope))
$(eval $(call import-library,type_traits))
$(eval $(call import-library,meta))

$(call add-build-library,cmoon.fixed_valarray,cmoon.fixed_valarray.underlying \
										 	   cmoon.fixed_valarray.expressions \
										 	   cmoon.fixed_valarray)
	$(call build-library)

$(call add-build-module-impl,cmoon.fixed_valarray,fixed_valarray.ixx \
							 					   $(build_directory)/cmoon.fixed_valarray.expressions.ifc \
							 					   $(build_directory)/cmoon.fixed_valarray.underlying.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_meta_library)) \
		$(call src-file,fixed_valarray.ixx)

$(call add-build-module-impl,cmoon.fixed_valarray.expressions,expressions.ixx, \
														 	   	cmoon.type_traits \
														 	   	cmoon.meta)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_meta_library)) \
		$(call src-file,expressions.ixx)

$(call add-build-module-impl,cmoon.fixed_valarray.underlying,underlying.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,underlying.ixx)

#-------------------------------

$(call add-bin-target,main.exe,main.cpp \
							   $(build_directory)/cmoon.fixed_valarray.lib, \
							   cmoon.meta)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_meta_library)) \
		$(call add-module-lib,cmoon.fixed_valarray) \
		$(call add-module-lib,cmoon.type_traits,$(cmoon_type_traits_library)) \
		$(call add-module-lib,cmoon.meta,$(cmoon_meta_library)) \
		$(call src-file,main.cpp)

main: $(bin_directory)/main.exe
	@$(bin_directory)/main.exe


# TESTS-----------------------------------------------------------------

$(call add-build-library,cmoon.tests.fixed_valarray,cmoon.tests.fixed_valarray)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.fixed_valarray,$(tests_directory)/fixed_valarray.ixx \
														 $(build_directory)/cmoon.fixed_valarray.ifc, \
											  			 	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call test-file,fixed_valarray.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.fixed_valarray.lib \
								$(build_directory)/cmoon.fixed_valarray.lib, \
									cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.fixed_valarray) \
		$(call add-module-lib,cmoon.tests.fixed_valarray) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.utility,$(cmoon_utility_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)