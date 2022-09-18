set(HEADERS_LIB
  generate.h
  lexer.h
  parser.h
  roman.h
  roman_literals.h
  token.h
)
set(SOURCES_LIB
  generate.cpp
  lexer.cpp
  parser.cpp
  roman.cpp
  roman_literals.cpp
)
add_library(roman_static STATIC ${HEADERS_LIB} ${SOURCES_LIB})
target_include_directories(roman_static PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
set_target_properties(roman_static PROPERTIES CXX_STANDARD 20)
# target_compile_features(roman_static PUBLIC cxx_std_20)

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
