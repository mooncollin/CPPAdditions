include $(TEMPLATE_BEGIN)
level=../../

$(call add-build-library,cmoon.ranges,cmoon.ranges.zip \
									  cmoon.ranges.enumerate \
									  cmoon.ranges.adjacent \
									  cmoon.ranges.to \
									  cmoon.ranges.utility \
									  cmoon.ranges)
	$(call build-library)

$(call add-build-module-impl,cmoon.ranges,ranges.ixx, \
									 	  cmoon.ranges.zip \
									 	  cmoon.ranges.enumerate \
									 	  cmoon.ranges.adjacent \
									 	  cmoon.ranges.to \
									 	  cmoon.ranges.utility)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,ranges.ixx)

$(call add-build-module-impl,cmoon.ranges.zip,zip.ixx, \
											  cmoon.tuple \
											  cmoon.utility \
											  cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,zip.ixx)

$(call add-build-module-impl,cmoon.ranges.enumerate,enumerate.ixx, \
											   		cmoon.ranges.zip)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,enumerate.ixx)

$(call add-build-module-impl,cmoon.ranges.adjacent,adjacent.ixx, \
											  	   cmoon.ranges.zip)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,adjacent.ixx)

$(call add-build-module-impl,cmoon.ranges.to,to.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,to.ixx)

$(call add-build-module-impl,cmoon.ranges.utility,utility.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,utility.ixx)

include $(TEMPLATE_END)