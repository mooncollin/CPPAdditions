override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.simd,cmoon.simd.m128 \
									cmoon.simd)
	$(call build-library)

$(call add-build-module-impl,cmoon.simd,simd.ixx, \
							 			cmoon.simd.m128)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,simd.ixx)

$(call add-build-module-impl,cmoon.simd.m128,m128.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,m128.ixx)

include $(CURDIR)/$(level)/Makefile_template_end