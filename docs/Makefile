override level :=../
include $(CURDIR)/$(level)/Makefile_template_begin

bin_directory := $(level)$(bin_directory)

$(call add-build-library,cmoon.docs,cmoon.docs \
									cmoon.docs.doc_template)
	$(call build-library)

$(call add-build-module-impl,cmoon.docs,docs.ixx, \
											cmoon.docs.doc_template)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,docs.ixx)

$(call add-build-module-impl,cmoon.docs.doc_template,doc_template.ixx, \
													 	cmoon.core)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call src-file,doc_template.ixx)

$(call add-bin-target,make_docs.exe,main.cpp, \
									cmoon.core \
									cmoon.docs)
	$(CXX) $(CXXFLAGS) $(CXXEXECUTABLE) \
		$(call src-file,main.cpp)

docs: $(bin_directory)/make_docs.exe
	@$(bin_directory)/make_docs.exe

include $(CURDIR)/$(level)/Makefile_template_end