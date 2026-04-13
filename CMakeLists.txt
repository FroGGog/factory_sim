cmake_minimum_required(VERSION 3.10)
project(factorySim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp ${PROJECT_SOURCE_DIR}/source/*/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

if(UNIX)
   find_package(raylib REQUIRED)
   target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
   add_library(raylib SHARED IMPORTED)
   set_target_properties(raylib PROPERTIES
      IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/raylib.dll
      IMPORTED_IMPLIB ${PROJECT_SOURCE_DIR}/lib/raylibdll.lib
      INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/lib)
   target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory"
)