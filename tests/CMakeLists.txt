set(HEADERS
)

set(SOURCES
  roman_tests.cpp
)

add_executable(roman_tests ${HEADERS} ${SOURCES})

target_link_libraries(roman_tests
  PRIVATE
    roman_static
)
