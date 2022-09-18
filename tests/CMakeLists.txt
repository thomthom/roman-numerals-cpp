set(HEADERS
  test_suite.h
)

set(SOURCES
  test_suite.cpp
)

set(TEST_SOURCES
  roman_tests.cpp
)

add_executable(roman_tests ${HEADERS} ${SOURCES} ${TEST_SOURCES})

target_link_libraries(roman_tests
  PRIVATE
    roman_static
)

if(CMAKE_CXX_COMPILER_ID EQUAL "MSVC")
  target_compile_options(roman_tests PRIVATE "/utf-8>")
endif()
