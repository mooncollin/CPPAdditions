include $(TEMPLATE_BEGIN)
level=../../

$(call add-build-library,cmoon.platform,cmoon.platform.architecture \
										cmoon.platform.compiler \
										cmoon.platform.operating_system \
										cmoon.platform.cpp_version \
										cmoon.platform.bits \
										cmoon.platform)
	$(call build-library)

$(call add-build-module-impl,cmoon.platform,platform.ixx, \
									   		cmoon.platform.architecture \
									   		cmoon.platform.compiler \
									   		cmoon.platform.operating_system \
									   		cmoon.platform.cpp_version \
									   		cmoon.platform.bits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,platform.ixx)

$(call add-build-module-impl,cmoon.platform.architecture,architecture.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,architecture.ixx)

$(call add-build-module-impl,cmoon.platform.compiler,compiler.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,compiler.ixx)

$(call add-build-module-impl,cmoon.platform.operating_system,operating_system.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,operating_system.ixx)

$(call add-build-module-impl,cmoon.platform.cpp_version,cpp_version.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,cpp_version.ixx)

$(call add-build-module-impl,cmoon.platform.bits,bits.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,bits.ixx)

include $(TEMPLATE_END)