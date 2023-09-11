cmake_minimum_required(VERSION 3.5)

project(SuperTuxScripter VERSION 0.1 LANGUAGES CXX)

option(USE_SUPERTUX "Add SuperTux integration" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

macro(cache_set var value type)
  set(${var} ${value} CACHE ${type} "" FORCE)
endmacro()

if(USE_SUPERTUX)
    cache_set(USE_SYSTEM_GLM OFF BOOL)
    #cache_set(GLM_ROOT_DIR ${PROJECT_SOURCE_DIR}/external/glm PATH)
    add_subdirectory(external/glm)

    cache_set(USE_SYSTEM_TINYGETTEXT ON BOOL)
    cache_set(TINYGETTEXT_WITH_SDL OFF BOOL)
    cache_set(TINYGETTEXT_PATH "${PROJECT_SOURCE_DIR}/external/tinygettext/" STRING)
    add_subdirectory(external/tinygettext)

    add_subdirectory(external/SDL_ttf)
endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Gui Quick QuickControls2 REQUIRED)
include(cmake/deps.cmake)

file(GLOB SRC src/*.cpp src/*.h)
file(GLOB_RECURSE QML src/qml/*.qml src/qml/*.js)
file(GLOB_RECURSE ASSETS assets/*)

qt_add_executable(SuperTuxScripter ${SRC})
qt_add_resources(SuperTuxScripter src/qml.qrc
    PREFIX_PATH "/"
    BASE src/
    FILES ${QML}
)
qt_add_resources(SuperTuxScripter assets/assets.qrc
    PREFIX_PATH "/"
    BASE assets/
    FILES ${ASSETS}
)

target_link_libraries(SuperTuxScripter PUBLIC Qt::Core Qt::Gui Qt::Quick Qt::QuickControls2)

if(USE_SUPERTUX)
    add_external_target_dependency(SuperTuxScripter supertux2_lib)
endif()

target_include_directories(SuperTuxScripter PUBLIC src/)

if(USE_SUPERTUX)
    target_compile_definitions(SuperTuxScripter PUBLIC USE_SUPERTUX)
endif()

if(MSVC)
    # what??? ok...
    target_link_options(SuperTuxScripter PUBLIC "/ENTRY:mainCRTStartup")
endif()
