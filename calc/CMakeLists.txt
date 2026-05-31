cmake_minimum_required(VERSION 3.14)
project(calc LANGUAGES C CXX)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

message(STATUS "Downloading Raylib...")
FetchContent_Declare(
  raylib
  GIT_REPOSITORY  "https://github.com/raysan5/raylib.git"
  GIT_TAG         "6.0"
  GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(raylib)

set(SRCS
    "src/main.cpp"
    "src/Layout.cpp"
    "src/ViewFuncs.cpp"
    "src/Stats.cpp"
    "src/util/String.cpp"
    "src/calculator/Calc.cpp"
    "src/calculator/DigiOp.cpp"
    "lib/stb/stb_sprintf.c"
)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ./)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "Calc"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.dajack05.calc"
    MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
  )
endif()
