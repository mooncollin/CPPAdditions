include Makefile_template_begin

$(call add-build-library,cmoon.core,cmoon.core, \
									cmoon.platform \
									cmoon.type_traits \
									cmoon.concepts \
									cmoon.scope \
									cmoon.tuple \
									cmoon.utility \
									cmoon.meta \
									cmoon.ranges \
									cmoon.test \
									cmoon.named_tuple \
									cmoon.html)
	$(call build-library) \
		"$(build_directory)/*.lib"

$(call add-build-module-impl,cmoon.core,core.ixx, \
											cmoon.platform \
											cmoon.type_traits \
											cmoon.concepts \
											cmoon.scope \
											cmoon.tuple \
											cmoon.utility \
											cmoon.meta \
											cmoon.ranges \
											cmoon.test \
											cmoon.named_tuple \
											cmoon.html)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,core.ixx)

$(call add-bin-target,make_docs.exe,docs/src/main.cpp, \
									cmoon.core)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		docs/src/main.cpp

docs: $(bin_directory)/make_docs.exe
	@$(bin_directory)/make_docs.exe

include Makefile_template_end