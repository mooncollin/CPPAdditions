include $(TEMPLATE_BEGIN)

cmoon_concepts_library 		=$(call get-library,concepts)
cmoon_test_library 			=$(call get-library,test)
cmoon_ranges_library 		=$(call get-library,ranges)
cmoon_tuple_library 		=$(call get-library,tuple)
cmoon_scope_library 		=$(call get-library,scope)

$(call add-build-library,cmoon.utility,cmoon.utility.owner \
									   cmoon.utility.throw_on_error \
									   cmoon.utility.extent_type \
									   cmoon.utility.stopwatch \
									   cmoon.utility.as_unsigned \
									   cmoon.utility.copyable_box \
									   cmoon.utility)
	$(call build-library)

$(call add-build-library,cmoon.tests.utility,cmoon.tests.utility)
	$(call build-library)

$(call add-build-module,cmoon.utility,utility.ixx \
									  $(build_directory)/cmoon.utility.owner.ifc \
									  $(build_directory)/cmoon.utility.throw_on_error.ifc \
									  $(build_directory)/cmoon.utility.extent_type.ifc \
									  $(build_directory)/cmoon.utility.stopwatch.ifc \
									  $(build_directory)/cmoon.utility.as_unsigned.ifc \
									  $(build_directory)/cmoon.utility.copyable_box.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
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

$(call add-build-module,cmoon.tests.utility,$(tests_directory)/utility.ixx \
											$(build_directory)/cmoon.utility.ifc)
	$(call make-library-module,cmoon.test,$(cmoon_test_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call add-module-dir) \
		$(call test-file,utility.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp \
								$(build_directory)/cmoon.tests.utility.lib \
								$(build_directory)/cmoon.utility.lib)
	$(call make-library-lib,cmoon.concepts,$(cmoon_concepts_library))
	$(call make-library-lib,cmoon.test,$(cmoon_test_library))
	$(call make-library-lib,cmoon.ranges,$(cmoon_ranges_library))
	$(call make-library-lib,cmoon.tuple,$(cmoon_tuple_library))
	$(call make-library-lib,cmoon.scope,$(cmoon_scope_library))
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