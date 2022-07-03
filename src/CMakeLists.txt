set(HEADERS_LIB
  roman.h
)
set(SOURCES_LIB
  roman.cpp
)
add_library(roman_static STATIC ${HEADERS_LIB} ${SOURCES_LIB})
target_include_directories(roman_static PUBLIC "${CMAKE_CURRENT_LIST_DIR}")


set(HEADERS
)
set(SOURCES
  main.cpp
)
add_executable(roman ${HEADERS} ${SOURCES})
target_link_libraries(roman
  PRIVATE
    roman_static
)
