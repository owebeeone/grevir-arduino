cmake_minimum_required(VERSION 3.20)
file(MAKE_DIRECTORY "${LOG_DIR}")
set(flags -std=c++23 -DHAS_STD_LIB=1 -DGREVIR_ARDUINO_HOST_MOCK -fsyntax-only)
foreach(directory IN LISTS INCLUDE_DIRS)
  if(NOT directory STREQUAL "")
    list(APPEND flags "-I${directory}")
  endif()
endforeach()

# CASE 0: two distinct pins. CASE 1: Serial plus LED.
# CASE 2: two modules share pin 13. CASE 3: two SerialIO<0> modules.
foreach(case IN ITEMS 0 1 2 3)
  execute_process(COMMAND "${CXX}" ${flags} "-DCASE_ID=${case}" "${CASE_SOURCE}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE errors)
  file(WRITE "${LOG_DIR}/case-${case}.log" "${output}${errors}")
  if(case LESS 2)
    if(NOT result STREQUAL "0")
      message(FATAL_ERROR "Valid Arduino claim case ${case} failed:\n${output}${errors}")
    endif()
  elseif(NOT result MATCHES "^[1-9][0-9]*$" OR
      NOT errors MATCHES "static assertion failed[^\n]*Application has resource conflict")
    message(FATAL_ERROR "Expected Arduino claim conflict for case ${case}, got ${result}:\n${output}${errors}")
  endif()
endforeach()
message(STATUS "Arduino claim probes: two valid applications and two expected conflicts passed")
