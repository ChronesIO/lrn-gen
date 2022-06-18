file(GLOB_RECURSE lrn-gen-impl CONFIGURE_DEPENDS "*.cxx")
target_sources(lrn-gen PUBLIC ${lrn-gen-impl})