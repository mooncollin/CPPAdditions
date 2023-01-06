include $(TEMPLATE_BEGIN)

cmoon_concepts_library 		=$(call get-library,concepts)
cmoon_utility_library 		=$(call get-library,utility)
cmoon_scope_library 		=$(call get-library,scope)
cmoon_ranges_library 		=$(call get-library,ranges)
cmoon_type_traits_library 	=$(call get-library,type_traits)
cmoon_tuple_library 		=$(call get-library,tuple)

$(call add-build-library,cmoon.test,cmoon.test.assert_exception \
									cmoon.test.assert \
									cmoon.test.test_result \
									cmoon.test.test_case \
									cmoon.test.test_suite \
									cmoon.test.text_test_runner \
									cmoon.test)
	$(call build-library)

$(call add-build-module-impl,cmoon.test,test.ixx \
								   $(build_directory)/cmoon.test.assert_exception.ifc \
								   $(build_directory)/cmoon.test.assert.ifc \
								   $(build_directory)/cmoon.test.test_result.ifc \
								   $(build_directory)/cmoon.test.test_case.ifc \
								   $(build_directory)/cmoon.test.test_suite.ifc \
								   $(build_directory)/cmoon.test.text_test_runner.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,test.ixx)

$(call add-build-module-impl,cmoon.test.assert_exception,assert_exception.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,assert_exception.ixx)

$(call add-build-module-impl,cmoon.test.assert,assert.ixx \
										  $(build_directory)/cmoon.test.assert_exception.ifc)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(call make-library-module,cmoon.type_traits,$(cmoon_type_traits_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call src-file,assert.ixx)

$(call add-build-module-impl,cmoon.test.test_result,test_result.ixx \
											   $(build_directory)/cmoon.test.assert_exception.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,test_result.ixx)

$(call add-build-module-impl,cmoon.test.test_case,test_case.ixx \
											 $(build_directory)/cmoon.test.assert_exception.ifc \
											 $(build_directory)/cmoon.test.test_result.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,test_case.ixx)

$(call add-build-module-impl,cmoon.test.test_suite,test_suite.ixx \
											  $(build_directory)/cmoon.test.test_case.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,test_suite.ixx)

$(call add-build-module-impl,cmoon.test.text_test_runner,text_test_runner.ixx \
											  		$(build_directory)/cmoon.test.test_case.ifc \
											  		$(build_directory)/cmoon.test.test_suite.ifc \
											  		$(build_directory)/cmoon.test.test_result.ifc)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(call make-library-module,cmoon.utility,$(cmoon_utility_library))
	$(call make-library-module,cmoon.scope,$(cmoon_scope_library))
	$(call make-library-module,cmoon.ranges,$(cmoon_ranges_library))
	$(call make-library-module,cmoon.tuple,$(cmoon_tuple_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call src-file,text_test_runner.ixx)

include $(TEMPLATE_END)