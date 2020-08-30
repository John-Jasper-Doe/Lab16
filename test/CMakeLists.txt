# CMake file for test directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/test")

set(PROJECT_SRC
#  ${CMAKE_SOURCE_DIR}/src/
)

addtest("alltests"
  testsplit.cpp
  ${PROJECT_SRC}
)
