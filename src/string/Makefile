include $(TEMPLATE_BEGIN)
level=../../

$(call add-build-library,cmoon.string,cmoon.string.platform \
									  cmoon.string.character \
									  cmoon.string.algorithm \
									  cmoon.string)
	$(call build-library)


$(call add-build-module-impl,cmoon.string,string.ixx, \
									 	  cmoon.string.platform \
									 	  cmoon.string.character \
									 	  cmoon.string.algorithm)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,string.ixx)

$(call add-build-module-impl,cmoon.string.platform,platform.ixx, \
												   cmoon.platform)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,platform.ixx)

$(call add-build-module-impl,cmoon.string.character,character.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,character.ixx)

$(call add-build-module-impl,cmoon.string.algorithm,algorithm.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,algorithm.ixx)

# TESTS--------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.string,cmoon.tests.string.algorithm \
											cmoon.tests.string)
	$(call build-library)

$(call add-build-module-impl,cmoon.tests.string.algorithm,$(tests_directory)/algorithm.ixx, \
													 	  cmoon.string \
														  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,algorithm.ixx)

$(call add-build-module-impl,cmoon.tests.string,$(tests_directory)/string.ixx, \
										   		cmoon.tests.string.algorithm \
												cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call test-file,string.ixx)

$(call add-bin-target,tests.exe,$(tests_directory)/main.cpp, \
								cmoon.tests.string \
								cmoon.string \
								cmoon.concepts \
								cmoon.test \
								cmoon.ranges \
								cmoon.tuple \
								cmoon.scope \
								cmoon.utility)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call test-file,main.cpp)

tests: $(bin_directory)/tests.exe
	$(bin_directory)/tests.exe

include $(TEMPLATE_END)