include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.utility.lib)

$(eval $(call import-library,concepts))
$(eval $(call import-library,test))
$(eval $(call import-library,ranges))
$(eval $(call import-library,tuple))
$(eval $(call import-library,scope))

$(call add-build-library,cmoon.utility,cmoon.utility.owner \
									   cmoon.utility.throw_on_error \
									   cmoon.utility.extent_type \
									   cmoon.utility.stopwatch \
									   cmoon.utility.as_unsigned \
									   cmoon.utility.copyable_box \
									   cmoon.utility.decay_copy \
									   cmoon.utility)
	$(call build-library)

$(call add-build-library,cmoon.tests.utility,cmoon.tests.utility)
	$(call build-library)

$(call add-build-module-impl,cmoon.utility,utility.ixx \
									  $(build_directory)/cmoon.utility.owner.ifc \
									  $(build_directory)/cmoon.utility.throw_on_error.ifc \
									  $(build_directory)/cmoon.utility.extent_type.ifc \
									  $(build_directory)/cmoon.utility.stopwatch.ifc \
									  $(build_directory)/cmoon.utility.as_unsigned.ifc \
									  $(build_directory)/cmoon.utility.decay_copy.ifc \
									  $(build_directory)/cmoon.utility.copyable_box.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,utility.ixx)

$(call add-build-module-impl,cmoon.utility.owner,owner.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,owner.ixx)

$(call add-build-module-impl,cmoon.utility.throw_on_error,throw_on_error.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,throw_on_error.ixx)

$(call add-build-module-impl,cmoon.utility.extent_type,extent_type.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,extent_type.ixx)

$(call add-build-module-impl,cmoon.utility.stopwatch,stopwatch.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,stopwatch.ixx)

$(call add-build-module-impl,cmoon.utility.as_unsigned,as_unsigned.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,as_unsigned.ixx)

$(call add-build-module-impl,cmoon.utility.copyable_box,copyable_box.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,copyable_box.ixx)

$(call add-build-module-impl,cmoon.utility.decay_copy,decay_copy.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,decay_copy.ixx)

$(call add-build-module-impl,cmoon.tests.utility,$(tests_directory)/utility.ixx \
												 $(build_directory)/cmoon.utility.ifc, \
												 	cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call test-file,utility.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.utility.lib \
								$(build_directory)/cmoon.utility.lib, \
									cmoon.concepts \
									cmoon.test \
									cmoon.ranges \
									cmoon.tuple \
									cmoon.scope)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-lib,cmoon.test,$(cmoon_test_library)) \
		$(call add-module-lib,cmoon.ranges,$(cmoon_ranges_library)) \
		$(call add-module-lib,cmoon.tuple,$(cmoon_tuple_library)) \
		$(call add-module-lib,cmoon.scope,$(cmoon_scope_library)) \
		$(call add-module-lib,cmoon.utility) \
		$(call add-module-lib,cmoon.tests.utility) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)