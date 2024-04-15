# Set the source directory for the library
set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Gather all source files in the lib directory
file(GLOB lib_SRC_FILES "${LIB_SRC_DIR}/*.cpp")

# Create a library target
add_library(msk_lib STATIC ${lib_SRC_FILES})

# Include directories for the library
target_include_directories(msk_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link any dependencies if needed
# target_link_libraries(msk_lib ${SOME_LIBRARY})

# Optionally, set compiler flags or other properties
# target_compile_options(msk_lib PRIVATE -Wall)

# Optionally, specify C++ standard
# target_compile_features(msk_lib PUBLIC cxx_std_11)
