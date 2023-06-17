override level :=../../
include $(CURDIR)/$(level)/Makefile_template_begin

$(call add-build-library,cmoon.type_traits,cmoon.type_traits.copy_traits \
										   cmoon.type_traits.is_any_of \
										   cmoon.type_traits.is_unique \
										   cmoon.type_traits.is_string_literal \
										   cmoon.type_traits.is_character \
										   cmoon.type_traits.detector \
										   cmoon.type_traits.is_specialization \
										   cmoon.type_traits.function_traits \
										   cmoon.type_traits)
	$(call build-library)

$(call add-build-module,cmoon.type_traits,type_traits.ixx, \
										  cmoon.type_traits.copy_traits \
										  cmoon.type_traits.is_any_of \
										  cmoon.type_traits.is_unique \
										  cmoon.type_traits.is_string_literal \
										  cmoon.type_traits.is_character \
										  cmoon.type_traits.detector \
										  cmoon.type_traits.is_specialization \
										  cmoon.type_traits.function_traits)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,type_traits.ixx)

$(call add-build-module,cmoon.type_traits.copy_traits,copy_traits.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,copy_traits.ixx)

$(call add-build-module,cmoon.type_traits.is_any_of,is_any_of.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,is_any_of.ixx)

$(call add-build-module,cmoon.type_traits.is_unique,is_unique.ixx, \
													cmoon.type_traits.is_any_of)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
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

$(call add-build-module,cmoon.type_traits.function_traits,function_traits.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,function_traits.ixx)

include $(CURDIR)/$(level)/Makefile_template_end