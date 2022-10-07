include $(TEMPLATE_BEGIN)

cmoon_tuple_library 	=$(call get-library,tuple)
cmoon_utility_library 	=$(call get-library,utility)
cmoon_concepts_library 	=$(call get-library,concepts)

$(call add-build-library,cmoon.ranges,cmoon.ranges.zip \
									  cmoon.ranges.enumerate \
									  cmoon.ranges.adjacent \
									  cmoon.ranges.to \
									  cmoon.ranges.utility \
									  cmoon.ranges)
	$(call build-library)

$(call add-build-module,cmoon.ranges,ranges.ixx \
									 $(build_directory)/cmoon.ranges.zip.ifc \
									 $(build_directory)/cmoon.ranges.enumerate.ifc \
									 $(build_directory)/cmoon.ranges.adjacent.ifc \
									 $(build_directory)/cmoon.ranges.to.ifc \
									 $(build_directory)/cmoon.ranges.utility.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,ranges.ixx)

$(call add-build-module,cmoon.ranges.zip,zip.ixx)
	$(call make-library-module,cmoon.tuple,$(cmoon_tuple_library))
	$(call make-library-module,cmoon.utility,$(cmoon_utility_library))
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,zip.ixx)

$(call add-build-module,cmoon.ranges.enumerate,enumerate.ixx \
											   $(build_directory)/cmoon.ranges.zip.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,enumerate.ixx)

$(call add-build-module,cmoon.ranges.adjacent,adjacent.ixx \
											  $(build_directory)/cmoon.ranges.zip.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,adjacent.ixx)

$(call add-build-module,cmoon.ranges.to,to.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,to.ixx)

$(call add-build-module,cmoon.ranges.utility,utility.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,utility.ixx)

include $(TEMPLATE_END)