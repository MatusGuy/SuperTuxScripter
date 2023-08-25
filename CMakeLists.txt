cmake_minimum_required(VERSION 3.5)

project(SuperTuxScripter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "assets/interface/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_subdirectory(external/sexp-cpp)
add_subdirectory(external/squirrel)

file(GLOB SRC src/*.cpp src/*.h)
file(GLOB UI assets/interface/*.ui)
file(GLOB QRC assets/*.qrc)

qt_add_executable(SuperTuxScripter ${SRC} ${UI} ${QRC}
    .gitignore)

target_link_libraries(SuperTuxScripter PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    squirrel
    sexp
)

target_include_directories(SuperTuxScripter PUBLIC src/ external/squirrel/include)
