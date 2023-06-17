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
	$(call build-library)

$(call add-build-module,cmoon.core,core.ixx, \
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
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,core.ixx)

include Makefile_template_end