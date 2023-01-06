include $(TEMPLATE_BEGIN)

cmoon_concepts_library =$(call get-library,concepts)

$(call add-build-library,cmoon.scope,cmoon.scope.scope_exit \
									 cmoon.scope.scope_fail \
									 cmoon.scope.scope_success \
									 cmoon.scope.unique_resource \
									 cmoon.scope)
	$(call build-library)

$(call add-build-module-impl,cmoon.scope,scope.ixx \
									$(build_directory)/cmoon.scope.scope_exit.ifc \
									$(build_directory)/cmoon.scope.scope_fail.ifc \
									$(build_directory)/cmoon.scope.scope_success.ifc \
									$(build_directory)/cmoon.scope.unique_resource.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,scope.ixx)

$(call add-build-module-impl,cmoon.scope.scope_exit,scope_exit.ixx)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,scope_exit.ixx)

$(call add-build-module-impl,cmoon.scope.scope_fail,scope_fail.ixx)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,scope_fail.ixx)

$(call add-build-module-impl,cmoon.scope.scope_success,scope_success.ixx)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,scope_success.ixx)

$(call add-build-module-impl,cmoon.scope.unique_resource,unique_resource.ixx)
	$(call make-library-module,cmoon.concepts,$(cmoon_concepts_library))
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call src-file,unique_resource.ixx)

include $(TEMPLATE_END)