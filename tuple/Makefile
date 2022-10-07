include $(TEMPLATE_BEGIN)

$(call add-build-library,cmoon.tuple,cmoon.tuple.tuple_like \
									 cmoon.tuple.for_each \
									 cmoon.tuple.tuple_transform \
									 cmoon.tuple)
	$(call build-library)

$(call add-build-module,cmoon.tuple,tuple.ixx \
									$(build_directory)/cmoon.tuple.tuple_like.ifc \
									$(build_directory)/cmoon.tuple.for_each.ifc \
									$(build_directory)/cmoon.tuple.tuple_transform.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,tuple.ixx)

$(call add-build-module,cmoon.tuple.tuple_like,tuple_like.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,tuple_like.ixx)

$(call add-build-module,cmoon.tuple.for_each,for_each.ixx)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call src-file,for_each.ixx)

$(call add-build-module,cmoon.tuple.tuple_transform,tuple_transform.ixx \
													$(build_directory)/cmoon.tuple.tuple_like.ifc)
	$(CXX) $(CXXFLAGS) $(CXXMODULE) \
		$(call add-module-dir) \
		$(call src-file,tuple_transform.ixx)

include $(TEMPLATE_END)