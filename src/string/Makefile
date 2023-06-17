override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.string,cmoon.string.platform \
									  cmoon.string.character \
									  cmoon.string.algorithm \
									  cmoon.string)
	$(call build-library)


$(call add-build-module,cmoon.string,string.ixx, \
									 	  cmoon.string.platform \
									 	  cmoon.string.character \
									 	  cmoon.string.algorithm)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,string.ixx)

$(call add-build-module,cmoon.string.platform,platform.ixx, \
												   cmoon.platform)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,platform.ixx)

$(call add-build-module,cmoon.string.character,character.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,character.ixx)

$(call add-build-module,cmoon.string.algorithm,algorithm.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,algorithm.ixx)

# TESTS--------------------------------------------------------------------------------------

$(call add-build-library,cmoon.tests.string,cmoon.tests.string.algorithm \
											cmoon.tests.string)
	$(call build-library)

$(call add-build-module,cmoon.tests.string.algorithm,$(tests_directory)/algorithm.ixx, \
													 	  cmoon.string \
														  cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call test-file,algorithm.ixx)

$(call add-build-module,cmoon.tests.string,$(tests_directory)/string.ixx, \
										   		cmoon.tests.string.algorithm \
												cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
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

include $(CURDIR)/$(level)/Makefile_template_end