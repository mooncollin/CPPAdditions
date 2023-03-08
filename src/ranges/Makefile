include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.ranges.lib)

$(eval $(call import-library,tuple))
$(eval $(call import-library,utility))
$(eval $(call import-library,concepts))

$(call add-build-library,cmoon.ranges,cmoon.ranges.zip \
									  cmoon.ranges.enumerate \
									  cmoon.ranges.adjacent \
									  cmoon.ranges.to \
									  cmoon.ranges.utility \
									  cmoon.ranges)
	$(call build-library)

$(call add-build-module-impl,cmoon.ranges,ranges.ixx \
									 $(build_directory)/cmoon.ranges.zip.ifc \
									 $(build_directory)/cmoon.ranges.enumerate.ifc \
									 $(build_directory)/cmoon.ranges.adjacent.ifc \
									 $(build_directory)/cmoon.ranges.to.ifc \
									 $(build_directory)/cmoon.ranges.utility.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,ranges.ixx)

$(call add-build-module-impl,cmoon.ranges.zip,zip.ixx, \
											  	cmoon.tuple \
												cmoon.utility \
												cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,zip.ixx)

$(call add-build-module-impl,cmoon.ranges.enumerate,enumerate.ixx \
											   $(build_directory)/cmoon.ranges.zip.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,enumerate.ixx)

$(call add-build-module-impl,cmoon.ranges.adjacent,adjacent.ixx \
											  $(build_directory)/cmoon.ranges.zip.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call src-file,adjacent.ixx)

$(call add-build-module-impl,cmoon.ranges.to,to.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,to.ixx)

$(call add-build-module-impl,cmoon.ranges.utility,utility.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,utility.ixx)

include $(TEMPLATE_END)