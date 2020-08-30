# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/src")

set(PROJECT_NAME1 rclst)
set(PROJECT_NAME2 rclss)

add_executable(${PROJECT_NAME1} rclst.cpp core/clusterization.cpp)
target_include_directories(${PROJECT_NAME1} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME1}
  pthread
  dlib
  openblas
  ${Boost_LIBRARIES}
)

add_executable(${PROJECT_NAME2} rclss.cpp core/classification.cpp)
target_include_directories(${PROJECT_NAME2} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME2}
  pthread
  dlib
  openblas
  ${Boost_LIBRARIES}
)

# install to bin folder our binaries
install(TARGETS ${PROJECT_NAME1} ${PROJECT_NAME2} RUNTIME DESTINATION bin)
