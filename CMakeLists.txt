cmake_minimum_required(VERSION 3.22.0)
project(DeltaGL VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
include(FetchContent)
set (CMAKE_CXX_STANDARD 17)

enable_testing()
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.2
)
FetchContent_MakeAvailable(SDL2)



add_executable(DeltaGL Src/main.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(DeltaGL SDL2::SDL2main SDL2::SDL2-static)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
