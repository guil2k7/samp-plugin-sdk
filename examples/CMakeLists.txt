add_library(HelloWorld SHARED HelloWorld.cc)
target_link_libraries(HelloWorld PRIVATE samp-plugin-sdk)
set_target_properties(HelloWorld PROPERTIES PREFIX "")
