# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "libs/cqt/CMakeFiles/cqt_autogen.dir/AutogenUsed.txt"
  "libs/cqt/CMakeFiles/cqt_autogen.dir/ParseCache.txt"
  "libs/cqt/cqt_autogen"
  )
endif()
