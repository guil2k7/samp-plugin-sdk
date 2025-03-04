add_library(Example1 SHARED HelloWorld.cc)
target_link_libraries(Example1 PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,samp-plugin-sdk>")
set_target_properties(Example1 PROPERTIES PREFIX "")

add_library(Example2 SHARED Uname.cc)
target_link_libraries(Example2 PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,samp-plugin-sdk>")
set_target_properties(Example2 PROPERTIES PREFIX "")

add_library(Example3 SHARED VariadicArgs.cc)
target_link_libraries(Example3 PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,samp-plugin-sdk>")
set_target_properties(Example3 PROPERTIES PREFIX "")
