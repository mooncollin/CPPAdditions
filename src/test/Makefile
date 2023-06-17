override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.test,cmoon.test.assert_exception \
									cmoon.test.assert \
									cmoon.test.test_result \
									cmoon.test.test_case \
									cmoon.test.test_suite \
									cmoon.test.text_test_runner \
									cmoon.test)
	$(call build-library)

$(call add-build-module,cmoon.test,test.ixx, \
							 	   cmoon.test.assert_exception \
							 	   cmoon.test.assert \
							 	   cmoon.test.test_result \
							 	   cmoon.test.test_case \
							 	   cmoon.test.test_suite \
							 	   cmoon.test.text_test_runner)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,test.ixx)

$(call add-build-module,cmoon.test.assert_exception,assert_exception.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,assert_exception.ixx)

$(call add-build-module,cmoon.test.assert,assert.ixx, \
							 			  cmoon.test.assert_exception \
										  cmoon.type_traits \
							 			  cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,assert.ixx)

$(call add-build-module,cmoon.test.test_result,test_result.ixx, \
											   cmoon.test.assert_exception)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,test_result.ixx)

$(call add-build-module,cmoon.test.test_case,test_case.ixx, \
											 cmoon.test.assert_exception \
											 cmoon.test.test_result)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,test_case.ixx)

$(call add-build-module,cmoon.test.test_suite,test_suite.ixx, \
											  cmoon.test.test_case)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,test_suite.ixx)

$(call add-build-module,cmoon.test.text_test_runner,text_test_runner.ixx, \
											  		cmoon.test.test_case \
											  		cmoon.test.test_suite \
											  		cmoon.test.test_result \
													cmoon.utility \
													cmoon.scope \
													cmoon.ranges)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,text_test_runner.ixx)

include $(CURDIR)/$(level)/Makefile_template_end