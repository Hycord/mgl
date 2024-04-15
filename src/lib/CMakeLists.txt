include_directories(${msk_SOURCE_DIR})

# Set the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Gather all source files in the src directory
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")