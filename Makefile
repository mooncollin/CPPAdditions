include $(TEMPLATE_BEGIN)
.DEFAULT_GOAL :=$(call build-target,cmoon.core.lib)

$(eval $(call import-library,platform))
$(eval $(call import-library,type_traits))
$(eval $(call import-library,concepts))
$(eval $(call import-library,scope))
$(eval $(call import-library,tuple))
$(eval $(call import-library,utility))
$(eval $(call import-library,meta))
$(eval $(call import-library,ranges))
$(eval $(call import-library,test))

$(call add-build-library,cmoon.core,cmoon.core, \
										cmoon.platform \
										cmoon.type_traits \
										cmoon.concepts \
										cmoon.scope \
										cmoon.tuple \
										cmoon.utility \
										cmoon.meta \
										cmoon.ranges \
										cmoon.test)
	$(call build-library) \
		"$(cmoon_platform_library)/$(build_directory)/cmoon.platform.lib" \
		"$(cmoon_type_traits_library)/$(build_directory)/cmoon.type_traits.lib" \
		"$(cmoon_concepts_library)/$(build_directory)/cmoon.concepts.lib" \
		"$(cmoon_scope_library)/$(build_directory)/cmoon.scope.lib" \
		"$(cmoon_tuple_library)/$(build_directory)/cmoon.tuple.lib" \
		"$(cmoon_utility_library)/$(build_directory)/cmoon.utility.lib" \
		"$(cmoon_meta_library)/$(build_directory)/cmoon.meta.lib" \
		"$(cmoon_ranges_library)/$(build_directory)/cmoon.ranges.lib" \
		"$(cmoon_test_library)/$(build_directory)/cmoon.test.lib"
	$(call copy-file,$(call make-path,"$(cmoon_platform_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_type_traits_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_concepts_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_scope_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_tuple_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_utility_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_meta_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_ranges_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")
	$(call copy-file,$(call make-path,"$(cmoon_test_library)%$(build_directory)/*.$(module_file_extension)"),"$(build_directory)")

$(call add-build-module-impl,cmoon.core,core.ixx, \
											cmoon.platform \
											cmoon.type_traits \
											cmoon.concepts \
											cmoon.scope \
											cmoon.tuple \
											cmoon.utility \
											cmoon.meta \
											cmoon.ranges \
											cmoon.test)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) $(CXXIMPL) \
		$(call add-module-dir,$(cmoon_platform_library)) \
		$(call add-module-dir,$(cmoon_type_traits_library)) \
		$(call add-module-dir,$(cmoon_concepts_library)) \
		$(call add-module-dir,$(cmoon_scope_library)) \
		$(call add-module-dir,$(cmoon_tuple_library)) \
		$(call add-module-dir,$(cmoon_utility_library)) \
		$(call add-module-dir,$(cmoon_meta_library)) \
		$(call add-module-dir,$(cmoon_ranges_library)) \
		$(call add-module-dir,$(cmoon_test_library)) \
		$(call src-file,core.ixx)

clean-all:
	@$(MAKE) -C $(cmoon_platform_library) clean
	@$(MAKE) -C $(cmoon_platform_library) clean
	@$(MAKE) -C $(cmoon_type_traits_library) clean
	@$(MAKE) -C $(cmoon_concepts_library) clean
	@$(MAKE) -C $(cmoon_scope_library) clean
	@$(MAKE) -C $(cmoon_tuple_library) clean
	@$(MAKE) -C $(cmoon_utility_library) clean
	@$(MAKE) -C $(cmoon_meta_library) clean
	@$(MAKE) -C $(cmoon_ranges_library) clean
	@$(MAKE) -C $(cmoon_test_library) clean

include $(TEMPLATE_END)