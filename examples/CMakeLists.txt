add_library(HelloWorld SHARED HelloWorld.cc)
target_link_libraries(HelloWorld PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,samp-plugin-sdk>")
set_target_properties(HelloWorld PROPERTIES PREFIX "")

add_library(Uname SHARED Uname.cc)
target_link_libraries(Uname PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,samp-plugin-sdk>")
set_target_properties(Uname PROPERTIES PREFIX "")
