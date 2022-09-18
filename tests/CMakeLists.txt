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
