override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.tuple,cmoon.tuple.tuple_like \
									 cmoon.tuple.for_each \
									 cmoon.tuple.tuple_transform \
									 cmoon.tuple)
	$(call build-library)

$(call add-build-module-impl,cmoon.tuple,tuple.ixx, \
							 cmoon.tuple.tuple_like \
							 cmoon.tuple.for_each \
							 cmoon.tuple.tuple_transform)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,tuple.ixx)

$(call add-build-module-impl,cmoon.tuple.tuple_like,tuple_like.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,tuple_like.ixx)

$(call add-build-module-impl,cmoon.tuple.for_each,for_each.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,for_each.ixx)

$(call add-build-module-impl,cmoon.tuple.tuple_transform,tuple_transform.ixx, \
														 cmoon.tuple.tuple_like)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,tuple_transform.ixx)

include $(CURDIR)/$(level)/Makefile_template_end