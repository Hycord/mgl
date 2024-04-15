# Set the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Gather all source files in the src directory
file(GLOB_RECURSE mgl_SRC_FILES "${SRC_DIR}/*.cpp")

# Include directories for the main executable
include_directories(${CMAKE_SOURCE_DIR}/include)

# Include the source files in the executable target
add_executable(mgl ${mgl_SRC_FILES})

