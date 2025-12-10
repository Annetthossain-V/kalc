cmake_minimum_required(VERSION 3.16)
project(kalc LANGUAGES CXX)

set(CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")

add_executable(${PROJECT_NAME} ${SRCFILES})

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>: -O3 -march=x86-64-v2 -mtune=native -fno-plt -fstack-protector -Wall -Wextra -flto>
  $<$<CONFIG:Debug>: -O0 -g>
  -I${CMAKE_CURRENT_SOURCE_DIR}/src/
  -pthread
)

target_link_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>: -O2 -flto -Wl,-O2>
)

target_link_directories(${PROJECT_NAME} PRIVATE
  "/usr/local/lib/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs} gmp)
