override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.html,cmoon.html.tags \
									cmoon.html.element \
									cmoon.html.attributes \
									cmoon.html.make_attributes \
									cmoon.html.static_attributes \
									cmoon.html.no_attributes \
									cmoon.html.tag_concept \
									cmoon.html)
	$(call build-library)

$(call add-build-module-impl,cmoon.html,html.ixx, \
										cmoon.html.tag_concept \
										cmoon.html.no_attributes \
										cmoon.html.static_attributes \
										cmoon.html.make_attributes \
										cmoon.html.attributes \
										cmoon.html.element \
										cmoon.html.tags)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,html.ixx)

$(call add-build-module-impl,cmoon.html.tag_concept,tag_concept.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,tag_concept.ixx)

$(call add-build-module-impl,cmoon.html.no_attributes,no_attributes.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,no_attributes.ixx)

$(call add-build-module-impl,cmoon.html.element,element.ixx, \
												cmoon.html.tag_concept \
												cmoon.html.no_attributes)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,element.ixx)

$(call add-build-module-impl,cmoon.html.static_attributes,static_attributes.ixx, \
														  cmoon.meta \
														  cmoon.named_tuple)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,static_attributes.ixx)

$(call add-build-module-impl,cmoon.html.attributes,attributes.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,attributes.ixx)

$(call add-build-module-impl,cmoon.html.tags,tags.ixx, \
											 cmoon.html.no_attributes \
											 cmoon.html.element)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,tags.ixx)

$(call add-build-module-impl,cmoon.html.make_attributes,make_attributes.ixx, \
											 			cmoon.html.no_attributes \
													 	cmoon.html.static_attributes)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,make_attributes.ixx)


# TESTS-----------------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.html,cmoon.tests.html.element \
										  cmoon.tests.html.static_attributes \
										  cmoon.tests.html.attributes \
										  cmoon.tests.html)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.html,$(tests_directory)/html.ixx, \
											  cmoon.tests.html.attributes \
											  cmoon.tests.html.static_attributes \
											  cmoon.tests.html.element \
											  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,html.ixx)

$(call add-build-module-impl,cmoon.tests.html.attributes,$(tests_directory)/attributes.ixx, \
													 	 cmoon.html \
														 cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,attributes.ixx)

$(call add-build-module-impl,cmoon.tests.html.static_attributes,$(tests_directory)/static_attributes.ixx, \
													 	 		cmoon.html \
														 		cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,static_attributes.ixx)

$(call add-build-module-impl,cmoon.tests.html.element,$(tests_directory)/element.ixx, \
													  cmoon.html \
													  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,element.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.html \
								cmoon.tests.html \
								cmoon.test \
								cmoon.concepts \
								cmoon.utility \
								cmoon.ranges)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	@$(bin_directory)/tests.exe

include $(CURDIR)/$(level)/Makefile_template_end