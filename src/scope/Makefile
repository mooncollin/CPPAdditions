override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.scope,cmoon.scope.scope_exit \
									 cmoon.scope.scope_fail \
									 cmoon.scope.scope_success \
									 cmoon.scope.unique_resource \
									 cmoon.scope)
	$(call build-library)

$(call add-build-module,cmoon.scope,scope.ixx, \
									cmoon.scope.scope_exit \
									cmoon.scope.scope_fail \
									cmoon.scope.scope_success \
									cmoon.scope.unique_resource)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,scope.ixx)

$(call add-build-module,cmoon.scope.scope_exit,scope_exit.ixx, \
											   cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,scope_exit.ixx)

$(call add-build-module,cmoon.scope.scope_fail,scope_fail.ixx, \
											   cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,scope_fail.ixx)

$(call add-build-module,cmoon.scope.scope_success,scope_success.ixx, \
												  cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,scope_success.ixx)

$(call add-build-module,cmoon.scope.unique_resource,unique_resource.ixx, \
													cmoon.concepts)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,unique_resource.ixx)

include $(CURDIR)/$(level)/Makefile_template_end