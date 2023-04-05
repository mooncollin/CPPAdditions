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
									cmoon.test)
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
											cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,core.ixx)

include Makefile_template_end