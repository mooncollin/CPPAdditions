override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.simd,cmoon.simd.m128 \
									cmoon.simd)
	$(call build-library)

$(call add-build-module,cmoon.simd,simd.ixx, \
							 			cmoon.simd.m128)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,simd.ixx)

$(call add-build-module,cmoon.simd.m128,m128.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,m128.ixx)

include $(CURDIR)/$(level)/Makefile_template_end