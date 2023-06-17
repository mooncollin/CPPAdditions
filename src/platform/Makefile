override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.platform,cmoon.platform.architecture \
										cmoon.platform.compiler \
										cmoon.platform.operating_system \
										cmoon.platform.cpp_version \
										cmoon.platform.bits \
										cmoon.platform)
	$(call build-library)

$(call add-build-module,cmoon.platform,platform.ixx,\
											cmoon.platform.bits \
											cmoon.platform.cpp_version \
											cmoon.platform.operating_system \
											cmoon.platform.compiler \
											cmoon.platform.architecture)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,platform.ixx)

$(call add-build-module,cmoon.platform.architecture,architecture.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,architecture.ixx)

$(call add-build-module,cmoon.platform.compiler,compiler.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,compiler.ixx)

$(call add-build-module,cmoon.platform.operating_system,operating_system.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,operating_system.ixx)

$(call add-build-module,cmoon.platform.cpp_version,cpp_version.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,cpp_version.ixx)

$(call add-build-module,cmoon.platform.bits,bits.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,bits.ixx)

include $(CURDIR)/$(level)/Makefile_template_end