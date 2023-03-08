include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.test.lib)

$(eval $(call import-library,concepts))
$(eval $(call import-library,utility))
$(eval $(call import-library,scope))
$(eval $(call import-library,ranges))
$(eval $(call import-library,type_traits))
$(eval $(call import-library,tuple))

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
							 				   $(build_directory)/cmoon.test.assert_exception.ifc, \
							 				   	cmoon.concepts)
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
											  			 $(build_directory)/cmoon.test.test_result.ifc, \
														 	cmoon.utility \
														 	cmoon.scope \
														 	cmoon.ranges)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call src-file,text_test_runner.ixx)

include $(TEMPLATE_END)