include $(TEMPLATE_BEGIN)

$(call add-build-library,cmoon.type_traits,cmoon.type_traits.copy_traits \
										   cmoon.type_traits.is_any_of \
										   cmoon.type_traits.is_unique \
										   cmoon.type_traits.is_string_literal \
										   cmoon.type_traits.is_character \
										   cmoon.type_traits.detector \
										   cmoon.type_traits.is_specialization \
										   cmoon.type_traits)
	$(call build-library)

$(call add-build-module,cmoon.type_traits,type_traits.ixx \
										  $(build_directory)/cmoon.type_traits.copy_traits.ifc \
										  $(build_directory)/cmoon.type_traits.is_any_of.ifc \
										  $(build_directory)/cmoon.type_traits.is_unique.ifc \
										  $(build_directory)/cmoon.type_traits.is_string_literal.ifc \
										  $(build_directory)/cmoon.type_traits.is_character.ifc \
										  $(build_directory)/cmoon.type_traits.detector.ifc \
										  $(build_directory)/cmoon.type_traits.is_specialization.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,type_traits.ixx)

$(call add-build-module,cmoon.type_traits.copy_traits,copy_traits.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,copy_traits.ixx)

$(call add-build-module,cmoon.type_traits.is_any_of,is_any_of.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,is_any_of.ixx)

$(call add-build-module,cmoon.type_traits.is_unique,is_unique.ixx \
													$(build_directory)/cmoon.type_traits.is_any_of.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,is_unique.ixx)

$(call add-build-module,cmoon.type_traits.is_string_literal,is_string_literal.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,is_string_literal.ixx)

$(call add-build-module,cmoon.type_traits.is_character,is_character.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,is_character.ixx)

$(call add-build-module,cmoon.type_traits.detector,detector.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,detector.ixx)

$(call add-build-module,cmoon.type_traits.is_specialization,is_specialization.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,is_specialization.ixx)

include $(TEMPLATE_END)