cmake_minimum_required(VERSION 2.8.12)
project(asf)

# Configures the compiler, regardless of the build type.
if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  add_definitions(-std=c++11
                  -stdlib=libc++
                  -Weverything
                  -Wno-c++98-compat
                  -Wno-missing-prototypes
                  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-std=c++11
                  -Wall
                  -Wextra
                  -Wpedantic
                  )
endif()

#
# If `git` is installed locally, perform an automatic update of submodules.
#
find_package(Git)
if(GIT_FOUND)
  message("Updating Git submodules with ${GIT_EXECUTABLE} ${GIT_VERSION_STRING}")
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule init)
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update)
endif(GIT_FOUND)

#
# Use `make doc` to generate API documentation.
#
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
          DESTINATION doc)
endif(DOXYGEN_FOUND)


# Adds the include directory to the compiler's search path.
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/external/any/include
  )

# Header files installed with the library.
set(
  LIBRARY_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/asf.hpp
)

# Builds the test drivers.
enable_testing()

#add_executable(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TEST.cpp)
#add_test(TEST TEST)

add_executable(test-format-neg01 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-neg01.cpp)
add_test(test-format-neg01 test-format-neg01)

add_executable(test-format-neg02 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-neg02.cpp)
add_test(test-format-neg02 test-format-neg02)

add_executable(test-format-pos01 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-pos01.cpp)
add_test(test-format-pos01 test-format-pos01)

add_executable(test-format-pos02 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-pos02.cpp)
add_test(test-format-pos02 test-format-pos02)

add_executable(test-format-pos03 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-pos03.cpp)
add_test(test-format-pos03 test-format-pos03)

add_executable(test-format-pos04 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-pos04.cpp)
add_test(test-format-pos04 test-format-pos04)

add_executable(test-format-pos05 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-format-pos05.cpp)
add_test(test-format-pos05 test-format-pos05)

add_executable(test-map-operator-pos01 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-map-operator-pos01.cpp)
add_test(test-map-operator-pos01 test-map-operator-pos01)

add_executable(test-map-operator-pos02 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-map-operator-pos02.cpp)
add_test(test-map-operator-pos02 test-map-operator-pos02)

add_executable(test-vector-operator-pos01 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-vector-operator-pos01.cpp)
add_test(test-vector-operator-pos01 test-vector-operator-pos01)

add_executable(test-vector-operator-pos02 ${CMAKE_CURRENT_SOURCE_DIR}/test/test-vector-operator-pos02.cpp)
add_test(test-vector-operator-pos02 test-vector-operator-pos02)

