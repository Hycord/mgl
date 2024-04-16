cmake_minimum_required(VERSION 3.28.3)
project(mgl VERSION 0.1.0 LANGUAGES C CXX)


find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})


find_package(GLEW REQUIRED)
link_libraries(${GLEW_LIBRARIES})

find_package(glm REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries( mgl ${OPENGL_LIBRARIES} glfw glm::glm)