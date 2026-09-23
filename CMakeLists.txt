cmake_minimum_required(VERSION 3.20)
project(grevir_arduino VERSION 0.1.0 LANGUAGES CXX)

if(NOT TARGET grevir::base)
  find_package(grevir-base CONFIG REQUIRED)
endif()

foreach(dependency IN ITEMS time core peripherals)
  if(NOT TARGET grevir::${dependency})
    find_package(grevir-${dependency} CONFIG REQUIRED)
  endif()
endforeach()

add_library(grevir_arduino INTERFACE)
add_library(grevir::arduino ALIAS grevir_arduino)
set_target_properties(grevir_arduino PROPERTIES EXPORT_NAME arduino)
target_compile_features(grevir_arduino INTERFACE cxx_std_23)
target_link_libraries(grevir_arduino INTERFACE
  grevir::base grevir::time grevir::core grevir::peripherals)
target_include_directories(grevir_arduino INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

include(GNUInstallDirs)
install(TARGETS grevir_arduino EXPORT GrevirArduinoTargets)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING
  PATTERN "*.hpp" PATTERN "*.h")
install(EXPORT GrevirArduinoTargets NAMESPACE grevir::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-arduino)
install(FILES cmake/grevir-arduino-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/grevir-arduino)
install(FILES LICENSE.txt DESTINATION ${CMAKE_INSTALL_DATADIR}/grevir-arduino)

option(GREVIR_BUILD_COMPILE_CHECKS "Compile native headers and template users" OFF)
option(GREVIR_BUILD_HOST_TESTS "Run deterministic native behavior tests" OFF)
if(GREVIR_BUILD_HOST_TESTS)
  enable_testing()
endif()
if(GREVIR_BUILD_COMPILE_CHECKS OR GREVIR_BUILD_HOST_TESTS)
  add_subdirectory(tests)
endif()
