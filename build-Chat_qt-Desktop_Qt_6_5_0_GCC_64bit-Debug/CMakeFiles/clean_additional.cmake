# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appChat_qt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appChat_qt_autogen.dir/ParseCache.txt"
  "appChat_qt_autogen"
  )
endif()
