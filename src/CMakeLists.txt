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

if(CMAKE_CXX_COMPILER_ID EQUAL "MSVC")
  target_compile_options(roman_static PRIVATE "/utf-8>")
endif()
# target_compile_options(roman_static PRIVATE "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
# target_compile_options(roman_static PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

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
