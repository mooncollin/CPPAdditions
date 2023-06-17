override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.ranges,cmoon.ranges.zip \
									  cmoon.ranges.enumerate \
									  cmoon.ranges.adjacent \
									  cmoon.ranges.to \
									  cmoon.ranges.utility \
									  cmoon.ranges)
	$(call build-library)

$(call add-build-module,cmoon.ranges,ranges.ixx, \
									 cmoon.ranges.zip \
									 cmoon.ranges.enumerate \
									 cmoon.ranges.adjacent \
									 cmoon.ranges.to \
									 cmoon.ranges.utility)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,ranges.ixx)

$(call add-build-module,cmoon.ranges.zip,zip.ixx, \
										 cmoon.tuple \
										 cmoon.utility \
										 cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,zip.ixx)

$(call add-build-module,cmoon.ranges.enumerate,enumerate.ixx, \
											   cmoon.ranges.zip)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,enumerate.ixx)

$(call add-build-module,cmoon.ranges.adjacent,adjacent.ixx, \
											  cmoon.ranges.zip)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,adjacent.ixx)

$(call add-build-module,cmoon.ranges.to,to.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,to.ixx)

$(call add-build-module,cmoon.ranges.utility,utility.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,utility.ixx)

include $(CURDIR)/$(level)/Makefile_template_end