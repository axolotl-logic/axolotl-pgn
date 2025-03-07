cmake_minimum_required(VERSION 3.22)

project(pgne3k)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

include_directories("${CMAKE_SOURCE_DIR}/src/")

#
# Third Party Libraries
#
find_package(Criterion)
include_directories(CRITERION_INCLUDE_DIR)

#
# Parser Generation
#
find_package(BISON)
find_package(FLEX)

bison_target(
  PgnParser src/pgn/pgn.syntax.y ${CMAKE_CURRENT_BINARY_DIR}/pgn.syntax.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pgn.syntax.h)

flex_target(PgnScanner src/pgn/pgn.lex.l ${CMAKE_CURRENT_BINARY_DIR}/pgn.lex.c
            DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pgn.lex.h)

add_flex_bison_dependency(PgnScanner PgnParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# Interfaces
#
add_library(
  pgne3k-common SHARED
  src/common/smalloc.c
  src/common/smalloc.h
  src/common/symbol.c
  src/common/symbol.h
  src/common/tsv.c
  src/common/tsv.h
  src/common/io.c
  src/common/io.h
  src/common/satoi.h
  src/common/satoi.c)

add_library(
  pgne3k-pgn SHARED
  ${BISON_PgnParser_OUTPUTS}
  ${FLEX_PgnScanner_OUTPUTS}
  src/pgn/gameclock.c
  src/pgn/gameclock.h
  src/pgn/generation.c
  src/pgn/generation.h
  src/pgn/pgn.c
  src/pgn/pgn_frontend.c
  src/pgn/pgn_frontend.h
  src/pgn/pgn.h
  src/pgn/pgn.lex.l
  src/pgn/pgn_move.c
  src/pgn/pgn_move.h
  src/pgn/pgn.syntax.y
  src/pgn/pgn_tag.c
  src/pgn/pgn_tag.h
  src/pgn/tagspec.c
  src/pgn/tagspec.h)

target_link_libraries(pgne3k-pgn PUBLIC pgne3k-common)

#
# Frontend Executable
#
add_executable(pgne3k src/main.c)
target_link_libraries(pgne3k PUBLIC pgne3k-common)
target_link_libraries(pgne3k PUBLIC pgne3k-pgn)

#
# Fuzz
#
add_executable(pgne3k-fuzz fuzz/main.c)
target_link_libraries(pgne3k-fuzz PUBLIC pgne3k-common pgne3k-pgn)

#
# Tests
#
add_executable(
  pgne3k-test
  tests/common/test_satoi.c
  tests/common/test_tsv.c
  tests/pgn/test_symbol.c
  tests/pgn/test_pgn.c
  tests/pgn/test_tagspec.c
  tests/pgn/test_pgn_move.c
  tests/pgn/test_pgn_tag.c
  tests/pgn/test_gameclock.c
  tests/pgn/test_pgn_frontend.c)

target_link_libraries(pgne3k-test PUBLIC pgne3k-pgn pgne3k-common
                                         ${CRITERION_LIBRARY})

add_compile_options(pgne3k-test --coverage)
add_link_options(pgne3k-test -lgcov --coverage)

enable_testing()
add_test(NAME pgne3k-test COMMAND pgne3k-test)

#
# Custom Commands and Targets
#

# Build human written documentation
add_custom_target(docs mkdocs build -f "${CMAKE_SOURCE_DIR}/mkdocs.docs.yml")

# Build computer generated reports
add_custom_target(docs-reports mkdocs build -f
                               "${CMAKE_SOURCE_DIR}/mkdocs.reports.yml")

# Linting!
file(GLOB_RECURSE LINTABLE_FILES "${PROJECT_SOURCE_DIR}/src/*.c"
     "${PROJECT_SOURCE_DIR}/src/*.h")
add_custom_target(
  lint
  COMMAND clang-tidy -p ${PROJECT_BINARY_DIR} ${LINTABLE_FILES}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
