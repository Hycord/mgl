include_directories(${msk_SOURCE_DIR})

# Set the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Gather all source files in the src directory
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_subdirectory(lib)

# Include the source files in the executable target
add_executable(msk ${SRC_FILES})
# target_link_libraries( msk SKIA )
