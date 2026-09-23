file(GLOB_RECURSE public_headers CONFIGURE_DEPENDS RELATIVE
  "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.h")
set(header_sources)
foreach(header IN LISTS public_headers)
  string(MAKE_C_IDENTIFIER "${header}" identifier)
  set(source "${CMAKE_CURRENT_BINARY_DIR}/${identifier}.cpp")
  file(WRITE "${source}" "#include <${header}>\n")
  list(APPEND header_sources "${source}")
endforeach()

add_library(grevir_arduino_compile OBJECT native_compile.cpp ${header_sources})
target_link_libraries(grevir_arduino_compile PRIVATE grevir::arduino)
target_compile_definitions(grevir_arduino_compile PRIVATE GREVIR_ARDUINO_HOST_MOCK)
set_target_properties(grevir_arduino_compile PROPERTIES CXX_EXTENSIONS OFF)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "^(AppleClang|Clang|GNU)$")
  message(FATAL_ERROR "Arduino claim probes currently require a Clang/GNU driver")
endif()
add_custom_target(grevir_arduino_claim_checks ALL
  COMMAND "${CMAKE_COMMAND}"
    "-DCXX=${CMAKE_CXX_COMPILER}"
    "-DINCLUDE_DIRS=$<TARGET_PROPERTY:grevir_arduino_compile,INCLUDE_DIRECTORIES>"
    "-DCASE_SOURCE=${CMAKE_CURRENT_SOURCE_DIR}/claim_probe.cpp"
    "-DLOG_DIR=${CMAKE_CURRENT_BINARY_DIR}/claim-results"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/check_claims.cmake"
  COMMENT "Checking Arduino pin and serial claims"
  VERBATIM)
